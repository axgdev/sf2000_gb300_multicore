#ifndef __HAL_H
#define __HAL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "libretro.h"

// A struct to hold all the pointers to the stock firmware functions and variables
typedef struct {
    // libc functions
    int (*strcat)(char *dest, const char *src);
    int (*strncmp)(const char *s1, const char *s2, size_t n);
    char *(*strncpy)(char *dest, const char *src, size_t n);
    char *(*strchr)(const char *s, int c);
    char *(*strrchr)(const char *s, int c);
    char *(*strstr)(const char *haystack, const char *needle);
    int (*strcasecmp)(const char *s1, const char *s2);
    int (*strncasecmp)(const char *s1, const char *s2, size_t n);
    void *(*memchr)(const void *s, int c, size_t n);
    int (*tolower)(int c);
    int (*toupper)(int c);
    int (*isalnum)(int c);
    int (*isalpha)(int c);
    int (*isascii)(int c);
    int (*iscntrl)(int c);
    int (*isdigit)(int c);
    int (*isgraph)(int c);
    int (*islower)(int c);
    int (*isprint)(int c);
    int (*ispunct)(int c);
    int (*isspace)(int c);
    int (*isupper)(int c);
    int (*isxdigit)(int c);
    int (*toascii)(int c);
    int (*_tolower)(int c);
    int (*_toupper)(int c);
    int (*isnan)(double x);
    int (*isinf)(double x);
    long int (*strtol)(const char *nptr, char **endptr, int base);
    unsigned long int (*strtoul)(const char *nptr, char **endptr, int base);
    double (*strtod)(const char *nptr, char **endptr);
    void *(*sbrk)(ptrdiff_t increment);
    void *(*malloc)(size_t size);
    void (*free)(void *ptr);
    void *(*realloc)(void *ptr, size_t size);
    void *(*calloc)(size_t nmemb, size_t size);
    int (*vsnprintf)(char *str, size_t size, const char *format, va_list ap);
    int (*sprintf)(char *str, const char *format, ...);
    int (*vprintf)(const char *format, va_list ap);
    int (*printf)(const char *format, ...);
    int (*snprintf)(char *str, size_t size, const char *format, ...);
    int (*vsprintf)(char *str, const char *format, va_list ap);
    int (*rand)(void);
    void *(*memcpy)(void *dest, const void *src, size_t n);
    void *(*memset)(void *s, int c, size_t n);
    int (*memcmp)(const void *s1, const void *s2, size_t n);
    void *(*memmove)(void *dest, const void *src, size_t n);
    char *(*strcpy)(char *dest, const char *src);
    int (*strcmp)(const char *s1, const char *s2);
    size_t (*strlen)(const char *s);
    int (*atoi)(const char *nptr);
    time_t (*time)(time_t *t);
    struct tm *(*localtime)(const time_t *timep);
    int (*vsscanf)(const char *str, const char *format, va_list ap);
    int (*sscanf)(const char *str, const char *format, ...);
    int (*open)(const char *pathname, int flags, ...);
    ssize_t (*read)(int fd, void *buf, size_t count);
    ssize_t (*write)(int fd, const void *buf, size_t count);
    off_t (*lseek)(int fd, off_t offset, int whence);
    int (*close)(int fd);
    char *(*strdup)(const char *s);
    int (*fclose)(FILE *fp);
    int (*fflush)(FILE *fp);
    FILE *(*fopen)(const char *path, const char *mode);
    size_t (*fw_fread)(void *ptr, size_t size, size_t nmemb, FILE *stream);
    int (*fseeko)(FILE *stream, off_t offset, int whence);
    long (*ftell)(FILE *stream);
    off_t (*ftello)(FILE *stream);
    size_t (*fwrite)(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    char *(*fgets)(char *s, int size, FILE *stream);

    // Filesystem functions
    int (*fs_open)(const char *path, int oflag, int perms);
    int (*fs_close)(int fd);
    int64_t (*fs_lseek)(int fd, int64_t offset, int whence);
    ssize_t (*fs_read)(int fd, void *buf, size_t nbyte);
    ssize_t (*fs_write)(int fd, const void *buf, size_t nbyte);
    int (*fs_access)(const char *path, int mode);
    int (*fs_stat)(const char *path, void *sbuf);
    int (*fs_fstat)(int fd, void *sbuf);
    int (*fs_sync)(const char *path);
    int (*fs_mkdir)(const char *path, int mode);
    int (*fs_opendir)(const char *path);
    int (*fs_closedir)(int fd);
    ssize_t (*fs_readdir)(int fd, void *buffer);

    // TDS2 functions
    void (*osal_tds2_cache_flush)(void *buf, unsigned sz);
    void (*os_disable_interrupt)(void);
    void (*os_enable_interrupt)(void);
    int (*dly_tsk)(unsigned ms);
    uint32_t (*os_get_tick_count)(void);

    // Driver functions
    void (*get_vp_init_low_lcd_para)(struct vp_init_info *);
    void (*switch_lcd_or_tv)(int is_lcd, int tvsys);
    int (*vpo_ioctl)(void* handle, uint32_t, uintptr_t);
    int (*osddrv_open)(void* handle, void *);
    int (*osddrv_close)(void* handle);
    int (*osddrv_3x_create_region)(void* handle, uint8_t, void *, void *);
    int (*osddrv_3x_region_write)(void* handle, uint8_t, void *, void *);
    int (*osddrv_scale)(void* handle, uint32_t, uintptr_t);
    void* (*dev_get_by_id)(uint32_t, uint16_t);
    void (*st7789v_caset_raset)(unsigned start_column, unsigned start_row);
    void (*st7789v_ramwr)(void);

    // Libretro frontend functions
    void (*run_osd_region_write)(const void *, uint16_t, uint16_t, uint16_t);
    void (*run_screen_write)(const void *, int width, int height, uint pitch);
    void (*run_sound_advance)(void *, unsigned);
    void (*retro_video_refresh_cb)(const void *data, unsigned width, unsigned height, size_t pitch);
    size_t (*retro_audio_sample_batch_cb)(const int16_t *data, size_t frames);
    void (*retro_input_poll_cb)(void);
    int16_t (*retro_input_state_cb)(unsigned port, unsigned device, unsigned index, unsigned id);
    bool (*retro_environment_cb)(unsigned cmd, void *data);
    int (*run_emulator)(int load_state);
    void (*run_gba)(const char *filename, int load_state);

    // Data variables
    unsigned *RAMSIZE;
    int *g_errno;
    int *g_snd_task_flags;
    struct retro_game_info *g_retro_game_info;
    int (**gfn_state_load)(const char *);
    int (**gfn_state_save)(const char *);
    unsigned (**gfn_retro_get_region)(void);
    void (**gfn_get_system_av_info)(struct retro_system_av_info *info);
    bool (**gfn_retro_load_game)(const struct retro_game_info *game);
    void (**gfn_retro_unload_game)(void);
    void (**gfn_retro_run)(void);
    void (**gfn_frameskip)(int flag);
    unsigned *g_run_file_size;
    void **gp_buf_64m;
    unsigned char **_ctype_;

    // FPS Counter variables
    int **fw_fps_counter_enable;
    int **fw_fps_counter;
    char **fw_fps_counter_format;

    // Hardware registers
    volatile unsigned *PINMUXL;
    volatile unsigned *PINMUXT;
    volatile unsigned *GPIOLCTRL;
    volatile unsigned *GPIOTCTRL;
    const unsigned char *lcd_font;
} stock_api_t;

extern stock_api_t g_stock_api;

void hal_init(void);

#endif
