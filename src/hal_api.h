#ifndef __HAL_API_H
#define __HAL_API_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include "libretro.h"
#include "stockfw.h"
#include "dirent.h"

// Forward-declare structs and enums to resolve compiler warnings.
// Their full definitions are in stockfw.h or video_sf2000.h,
// but the compiler needs to know they are types when parsing this header.
struct vp_init_info;
enum tvsystem;
struct osdrect;
struct osdpara;
struct osd_vscr;

// Define HAL API struct to hold all stock firmware function pointers
typedef struct {
    // libc functions
    char* (*strcat)(char*, const char*);
    int (*strncmp)(const char*, const char*, size_t);
    char* (*strncpy)(char*, const char*, size_t);
    char* (*strchr)(const char*, int);
    char* (*strrchr)(const char*, int);
    char* (*strstr)(const char*, const char*);
    int (*strcasecmp)(const char*, const char*);
    int (*strncasecmp)(const char*, const char*, size_t);
    void* (*memchr)(const void*, int, size_t);
    int (*tolower)(int);
    int (*toupper)(int);
    int (*isalnum)(int);
    int (*isalpha)(int);
    int (*isascii)(int);
    int (*iscntrl)(int);
    int (*isdigit)(int);
    int (*isgraph)(int);
    int (*islower)(int);
    int (*isprint)(int);
    int (*ispunct)(int);
    int (*isspace)(int);
    int (*isupper)(int);
    int (*isxdigit)(int);
    int (*toascii)(int);
    int (*_tolower)(int);
    int (*_toupper)(int);
    int (*isnan)(double);
    int (*isinf)(double);
    long (*strtol)(const char*, char**, int);
    unsigned long (*strtoul)(const char*, char**, int);
    void* (*sbrk)(ptrdiff_t);
    void* (*malloc)(size_t);
    void (*free)(void*);
    void* (*realloc)(void*, size_t);
    void* (*calloc)(size_t, size_t);
    int (*vsnprintf)(char*, size_t, const char*, va_list);
    int (*sprintf)(char*, const char*, ...);
    int (*vprintf)(const char*, va_list);
    int (*printf)(const char*, ...);
    int (*snprintf)(char*, size_t, const char*, ...);
    int (*vsprintf)(char*, const char*, va_list);
    int (*rand)(void);
    void* (*memcpy)(void*, const void*, size_t);
    void* (*memset)(void*, int, size_t);
    int (*memcmp)(const void*, const void*, size_t);
    void* (*memmove)(void*, const void*, size_t);
    char* (*strcpy)(char*, const char*);
    int (*strcmp)(const char*, const char*);
    size_t (*strlen)(const char*);
    int (*atoi)(const char*);
    time_t (*time)(time_t*);
    struct tm* (*localtime)(const time_t*);
    int (*vsscanf)(const char*, const char*, va_list);
    int (*sscanf)(const char*, const char*, ...);
    char* (*strdup)(const char*);
    int (*fclose)(FILE*);
    int (*fflush)(FILE*);
    FILE* (*fopen)(const char*, const char*);
    size_t (*fw_fread)(void*, size_t, size_t, FILE*);
    int (*fseeko)(FILE*, off_t, int);
    long (*ftell)(FILE*);
    off_t (*ftello)(FILE*);
    size_t (*fwrite)(const void*, size_t, size_t, FILE*);
    char* (*fgets)(char*, int, FILE*);

    // Filesystem functions
    int (*fs_open)(const char*, int, int);
    int (*fs_close)(int);
    int64_t (*fs_lseek)(int, int64_t, int);
    ssize_t (*fs_read)(int, void*, size_t);
    ssize_t (*fs_write)(int, const void*, size_t);
    int (*fs_access)(const char*, int);
    int (*fs_stat)(const char*, void*);
    int (*fs_fstat)(int, void*);
    int (*fs_sync)(const char*);
    int (*fs_mkdir)(const char*, int);
    int (*fs_opendir)(const char*);
    int (*fs_closedir)(int);
    ssize_t (*fs_readdir)(int, void*);
    
    // TDS2 OS functions
    void (*osal_tds2_cache_flush)(void*, unsigned);
    void (*os_disable_interrupt)(void);
    void (*os_enable_interrupt)(void);
    int (*dly_tsk)(unsigned);
    uint32_t (*os_get_tick_count)(void);

    // Driver functions
    void (*get_vp_init_low_lcd_para)(struct vp_init_info*);
    void (*switch_lcd_or_tv)(BOOL, enum tvsystem);
    int (*vpo_ioctl)(HANDLE, uint32_t, uintptr_t);
    int (*osddrv_open)(HANDLE, void*);
    int (*osddrv_close)(HANDLE);
    int (*osddrv_3x_create_region)(HANDLE, uint8_t, struct osdrect*, struct osdpara*);
    int (*osddrv_3x_region_write)(HANDLE, uint8_t, struct osd_vscr*, struct osdrect*);
    int (*osddrv_scale)(HANDLE, uint32_t, uintptr_t);
    HANDLE (*dev_get_by_id)(uint32_t, uint16_t);
    void (*st7789v_caset_raset)(unsigned, unsigned);
    void (*st7789v_ramwr)(void);

    // Libretro frontend functions
    void (*run_osd_region_write)(const void*, uint16_t, uint16_t, uint16_t);
    void (*run_screen_write)(const void*, int, int, uint);
    void (*run_sound_advance)(void*, unsigned);
    bool (*retro_environment_cb)(unsigned, void*);
    void (*retro_video_refresh_cb)(const void*, unsigned, unsigned, size_t);
    size_t (*retro_audio_sample_batch_cb)(const int16_t*, size_t);
    void (*retro_input_poll_cb)(void);
    int16_t (*retro_input_state_cb)(unsigned, unsigned, unsigned, unsigned);
    int (*run_emulator)(int);
    void (*run_gba)(const char*, int);

    // Pointers to data
    const unsigned char** _ctype_;
    unsigned* RAMSIZE;
    int* g_errno;
    int* g_snd_task_flags;
    struct retro_game_info* g_retro_game_info;
    int (**gfn_state_load)(const char*);
    int (**gfn_state_save)(const char*);
    unsigned (**gfn_retro_get_region)(void);
    void (**gfn_get_system_av_info)(struct retro_system_av_info*);
    bool (**gfn_retro_load_game)(const struct retro_game_info*);
    void (**gfn_retro_unload_game)(void);
    void (**gfn_retro_run)(void);
    void (**gfn_frameskip)(BOOL);
    const unsigned* g_run_file_size;
    void** gp_buf_64m;
    
    // Hardware registers
    volatile unsigned* PINMUXL;
    volatile unsigned* PINMUXT;
    volatile unsigned* GPIOLCTRL;
    volatile unsigned* GPIOTCTRL;

} HAL_API;

extern HAL_API hal_api;

void hal_init(void);

#endif // __HAL_API_H