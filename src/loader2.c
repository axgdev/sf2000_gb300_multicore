#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libretro.h"
#include "core_api.h"
#include "stockfw.h"
#include "debug.h"

// This is Stage 2 loader, loaded at 0x87000000 by Stage 1
// It does all the work that main.c used to do.

#define MAXPATH 255
static char *corefile = NULL;
static char *romfile = NULL;
static char *tmpbuffer = NULL;

static int state_stub(const char *path) { return 1; }

static void restore_stock_gp()
{
    asm(
        "lui\t$gp, 0x80c1\t\t\t\t\n"
        "addiu\t$gp, $gp, 0x14f4\t\t\t\n"
    );
}

bool parse_filename(const char *file_path, const char**corename, const char **filename)
{
    char* s = strncpy(tmpbuffer, file_path, MAXPATH);
    *corename = s;

    char* p = strchr(s, ';');
    if (!p) return false;
    *(p++) = 0;

    char* pp = strrchr(s, '/');
    if (!pp) return false;
    *(pp++) = 0;

    *corename = pp;
    *filename = p;

    char* p2 = strrchr(p, '.');
    if (!p2) return false;
    *(p2) = 0;

    return true;
}

static void full_cache_flush()
{
    unsigned idx;
    for (idx = 0x80000000; idx <= 0x80004000; idx += 16)
        asm volatile("cache 1, 0(%0); cache 1, 0(%0)" : : "r"(idx));
    asm volatile("sync 0; nop; nop");
    for (idx = 0x80000000; idx <= 0x80004000; idx += 16)
        asm volatile("cache 0, 0(%0); cache 0, 0(%0)" : : "r"(idx));
    asm volatile("nop; nop; nop; nop; nop");
}

// loader2_entry must be placed at a known location in the binary (at the beginning)
// so that when the loader actually loads the binary into mem address 0x87000000,
// then loader2_entry will be the first function there for the loader to call.
void loader2_entry(const char *file_path, int load_state) __attribute__((section(".init.loader2_entry")));

void loader2_entry(const char *file_path, int load_state)
{
    // Clear BSS, etc.
    extern void *__bss_start;
    extern void *_end;
    memset(&__bss_start, 0, (char*)&_end-(char*)&__bss_start);
    lcd_init();
#if defined(CLEAR_LOG_ON_BOOT)
    xlog_clear();
#endif
    corefile = malloc(MAXPATH);
    romfile = malloc(MAXPATH);
    tmpbuffer = malloc(MAXPATH);

    // Patch $gp in IRQ handler (dynarec fix)
    #define PATCH_JAL(target, hook)  *(uint32_t*)(target) = (3 << 26) | (uint32_t)hook >> 2 & ((1 << 26) - 1)
    PATCH_JAL(0x80049744, restore_stock_gp);

    dbg_show_noblock(0x00, "\n I'm here yeaaahhhhh:\n\n %s\n\n ", file_path); 

    xlog("Stage2: run file=%s\n", file_path);

    // Parse stub file
    const char *corename;
    const char *filename;
    if (!parse_filename(file_path, &corename, &filename)) {
        xlog("Stage2: file not MC stub: calling run_gba\n");
        dbg_show_noblock(0x00, "\n STOCK\n\n %s\n\n ", file_path); // black
        run_gba(file_path, load_state);
        return;
    }

    dbg_show_noblock(0x00,"\n MULTICORE\n\n %s\n\n %s \n\n ", corename, filename); // black

    void *core_load_addr = (void*)0x87080000; // load core above loader2, adjust if needed

    FILE *pf;
    size_t core_size;

    g_snd_task_flags = g_snd_task_flags & 0xfffe;
    while (g_snd_task_flags != 0) {
        dly_tsk(1);
    }
    RAMSIZE = (unsigned)core_load_addr;

    snprintf(corefile, MAXPATH, "/mnt/sda1/cores/%s/core_87000000", corename);
    snprintf(romfile, MAXPATH, "/mnt/sda1/ROMS/%s/%s", corename, filename);

    xlog("Stage2: corefile=%s\n", corefile);
    xlog("Stage2: romfile=%s\n", romfile);

    pf = fopen(corefile, "rb");
    if (!pf) {
        xlog("Stage2: Error opening corefile\n");
        lcd_bsod("Stage2: Failed to load core file!");
        return;
    }

    fseeko(pf, 0, SEEK_END);
    core_size = ftell(pf);
    fseeko(pf, 0, SEEK_SET);
    fw_fread(core_load_addr, 1, core_size, pf);
    fclose(pf);

    xlog("Stage2: core loaded\n");

    full_cache_flush();
    xlog("Stage2: cache flushed\n");

    // core entry function at start of loaded binary
    core_entry_t core_entry = core_load_addr;
    struct retro_core_t *core_api = core_entry();

    gfn_state_load = state_stub;
    gfn_state_save = state_stub;

    core_api->retro_set_video_refresh(retro_video_refresh_cb);
    core_api->retro_set_audio_sample_batch(retro_audio_sample_batch_cb);
    core_api->retro_set_input_poll(retro_input_poll_cb);
    core_api->retro_set_input_state(retro_input_state_cb);
    core_api->retro_set_environment(retro_environment_cb);

    xlog("Stage2: retro_init\n");
    core_api->retro_init();

    g_retro_game_info.path = romfile;
    g_retro_game_info.data = gp_buf_64m;
    g_retro_game_info.size = g_run_file_size;

    gfn_retro_get_region    = core_api->retro_get_region;
    gfn_get_system_av_info  = core_api->retro_get_system_av_info;
    gfn_retro_load_game     = core_api->retro_load_game;
    gfn_retro_unload_game   = core_api->retro_unload_game;
    gfn_retro_run           = core_api->retro_run;

    xlog("Stage2: run_emulator(%d)\n", load_state);
    run_emulator(load_state);

    xlog("Stage2: retro_deinit\n");
    core_api->retro_deinit();
    // If we ever return, just show BSOD
    lcd_bsod("Stage2: Core returned!");
}
