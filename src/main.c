/* Copyright (C) 2023 Nikita Burnashev

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted.

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND! */

#include <string.h>
#include <stdint.h>
#include "stockfw.h"
#include "debug.h"

#define LOADER2_PATH "/mnt/sda1/loader2.bin"
#define LOADER2_ADDR ((void*)0x87000000)
#define LOADER2_MAX_SIZE (2*1024*1024) // 2MB safety margin

// Load a file into memory using firmware functions
static int load_file_firmware(const char* path, void* addr, size_t max_size) {
    int fd = fs_open(path, FS_O_RDONLY, 0);
    if (fd < 0) return -1;
    size_t total = 0;
    while (total < max_size) {
        ssize_t r = fs_read(fd, (uint8_t*)addr + total, max_size - total);
        if (r <= 0) break;
        total += r;
    }
    fs_close(fd);
    return total > 0 ? 0 : -2;
}

void full_cache_flush()
{
    unsigned idx;
    for (idx = 0x80000000; idx <= 0x80004000; idx += 16)
        asm volatile("cache 1, 0(%0); cache 1, 0(%0)" : : "r"(idx));
    asm volatile("sync 0; nop; nop");
    for (idx = 0x80000000; idx <= 0x80004000; idx += 16)
        asm volatile("cache 0, 0(%0); cache 0, 0(%0)" : : "r"(idx));
    asm volatile("nop; nop; nop; nop; nop");
}

// Entrypoint called by patched bisrv.asd
void load_and_run_core(const char *file_path, int load_state)
{
    lcd_init();
    dbg_show_noblock(0x0000, "Stage1: Loading loader2.bin...");
    if (load_file_firmware(LOADER2_PATH, LOADER2_ADDR, LOADER2_MAX_SIZE) != 0)
        lcd_bsod("Stage1: Failed to load loader2.bin!");
	
    // Debug: show first 4 bytes of loaded loader2.bin
    char msg[64];
    uint32_t *p = (uint32_t*)LOADER2_ADDR;
    snprintf(msg, sizeof(msg), "loader2: %08x", *p);
    dbg_show_noblock(0x0000, msg);

    full_cache_flush();
    // Jump to loader2_entry with stubfile and load_state as args
    void (*loader2_entry)(const char*, int) = (void(*)(const char*,int))LOADER2_ADDR;
    loader2_entry(file_path, load_state);
    // Should never return, but just in case
    lcd_bsod("Stage1: loader2.bin returned!");
}

void hook_sys_watchdog_reboot(void)
{
    unsigned ra;
    asm volatile ("move %0, $ra" : "=r" (ra));
    lcd_bsod("assert at 0x%08x", ra);
}

void hook_exception_handler(unsigned code)
{
    unsigned ra;
    asm volatile ("move %0, $ra" : "=r" (ra));
    lcd_bsod("exception %d at 0x%08x", code, ra);
}
