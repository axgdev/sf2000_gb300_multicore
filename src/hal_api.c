#include "hal_api.h"
#include "core_api.h"

// Use an illegal address as the default so bugs are easy to spot.
#define PLACEHOLDER_ADDR ((void*)0xDEADBEEF)

enum platform_t {
    PLATFORM_SF2000 = 0,
    PLATFORM_GB300v1  = 1,
    PLATFORM_UNKNOWN = -1,
};

unsigned short g_mxmv_screen_magic; // Magic value for screen mirroring
int *fw_fps_counter_enable;
int *fw_fps_counter;
char *fw_fps_counter_format;

struct hal_api {
    // File system functions
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
    
    // OS functions
    void (*osal_tds2_cache_flush)(void *buf, unsigned sz);
    void (*os_disable_interrupt)(void);
    void (*os_enable_interrupt)(void);
    int (*dly_tsk)(unsigned ms);
    uint32_t (*os_get_tick_count)(void);
    
    // Device functions
    HANDLE (*dev_get_by_id)(uint32_t, uint16_t);
    
    // Emulator functions
    int (*run_emulator)(int load_state);
    void (*run_gba)(const char *filename, int load_state);
    
    // Libretro callback functions
    void (*retro_video_refresh_cb)(const void *data, unsigned width, unsigned height, size_t pitch);
    size_t (*retro_audio_sample_batch_cb)(const int16_t *data, size_t frames);
    void (*retro_input_poll_cb)(void);
    int16_t (*retro_input_state_cb)(unsigned port, unsigned device, unsigned index, unsigned id);
    bool (*retro_environment_cb)(unsigned cmd, void *data);
    
    // Driver functions
    void *(*get_vp_init_low_lcd_para)(void);
    void (*switch_lcd_or_tv)(int mode);
    int (*vpo_ioctl)(int cmd, void *arg);
    int (*osddrv_open)(void);
    int (*osddrv_close)(void);
    int (*osddrv_3x_create_region)(void *params);
    int (*osddrv_3x_region_write)(void *params);
    int (*osddrv_scale)(void *params);
    void (*st7789v_caset_raset)(int x1, int y1, int x2, int y2);
    void (*st7789v_ramwr)(void);
    
    // Libretro frontend functions
    void (*run_osd_region_write)(void *params);
    void (*run_screen_write)(void *params);
    void (*run_sound_advance)(void);
    
    // Data symbol pointers
    unsigned *RAMSIZE_ptr;
    int *g_errno_ptr;
    int *g_snd_task_flags_ptr;
    struct retro_game_info *g_retro_game_info_ptr;
    int (**gfn_state_load_ptr)(const char *);
    int (**gfn_state_save_ptr)(const char *);
    unsigned (**gfn_retro_get_region_ptr)(void);
    void (**gfn_get_system_av_info_ptr)(struct retro_system_av_info *);
    bool (**gfn_retro_load_game_ptr)(const struct retro_game_info *);
    void (**gfn_retro_unload_game_ptr)(void);
    void (**gfn_retro_run_ptr)(void);
    void (**gfn_frameskip_ptr)(BOOL);
    // const unsigned *g_run_file_size_ptr;
    void **gp_buf_64m_ptr;
    
    // Hardware register pointers
    volatile uint32_t *PINMUXL_ptr;
    volatile uint32_t *PINMUXT_ptr;
    volatile uint32_t *GPIOLCTRL_ptr;
    volatile uint32_t *GPIOTCTRL_ptr;
};

struct hal_api g_hal_api = {
    .fs_open = PLACEHOLDER_ADDR,
    .fs_close = PLACEHOLDER_ADDR,
    .fs_lseek = PLACEHOLDER_ADDR,
    .fs_read = PLACEHOLDER_ADDR,
    .fs_write = PLACEHOLDER_ADDR,
    .fs_access = PLACEHOLDER_ADDR,
    .fs_stat = PLACEHOLDER_ADDR,
    .fs_fstat = PLACEHOLDER_ADDR,
    .fs_sync = PLACEHOLDER_ADDR,
    .fs_mkdir = PLACEHOLDER_ADDR,
    .fs_opendir = PLACEHOLDER_ADDR,
    .fs_closedir = PLACEHOLDER_ADDR,
    .fs_readdir = PLACEHOLDER_ADDR,
    .osal_tds2_cache_flush = PLACEHOLDER_ADDR,
    .os_disable_interrupt = PLACEHOLDER_ADDR,
    .os_enable_interrupt = PLACEHOLDER_ADDR,
    .dly_tsk = PLACEHOLDER_ADDR,
    .os_get_tick_count = PLACEHOLDER_ADDR,
    .dev_get_by_id = PLACEHOLDER_ADDR,
    .run_emulator = PLACEHOLDER_ADDR,
    .run_gba = PLACEHOLDER_ADDR,
    .retro_video_refresh_cb = PLACEHOLDER_ADDR,
    .retro_audio_sample_batch_cb = PLACEHOLDER_ADDR,
    .retro_input_poll_cb = PLACEHOLDER_ADDR,
    .retro_input_state_cb = PLACEHOLDER_ADDR,
    .retro_environment_cb = PLACEHOLDER_ADDR,
    .get_vp_init_low_lcd_para = PLACEHOLDER_ADDR,
    .switch_lcd_or_tv = PLACEHOLDER_ADDR,
    .vpo_ioctl = PLACEHOLDER_ADDR,
    .osddrv_open = PLACEHOLDER_ADDR,
    .osddrv_close = PLACEHOLDER_ADDR,
    .osddrv_3x_create_region = PLACEHOLDER_ADDR,
    .osddrv_3x_region_write = PLACEHOLDER_ADDR,
    .osddrv_scale = PLACEHOLDER_ADDR,
    .st7789v_caset_raset = PLACEHOLDER_ADDR,
    .st7789v_ramwr = PLACEHOLDER_ADDR,
    .run_osd_region_write = PLACEHOLDER_ADDR,
    .run_screen_write = PLACEHOLDER_ADDR,
    .run_sound_advance = PLACEHOLDER_ADDR,
    .RAMSIZE_ptr = PLACEHOLDER_ADDR,
    .g_errno_ptr = PLACEHOLDER_ADDR,
    .g_snd_task_flags_ptr = PLACEHOLDER_ADDR,
    .g_retro_game_info_ptr = PLACEHOLDER_ADDR,
    .gfn_state_load_ptr = PLACEHOLDER_ADDR,
    .gfn_state_save_ptr = PLACEHOLDER_ADDR,
    .gfn_retro_get_region_ptr = PLACEHOLDER_ADDR,
    .gfn_get_system_av_info_ptr = PLACEHOLDER_ADDR,
    .gfn_retro_load_game_ptr = PLACEHOLDER_ADDR,
    .gfn_retro_unload_game_ptr = PLACEHOLDER_ADDR,
    .gfn_retro_run_ptr = PLACEHOLDER_ADDR,
    .gfn_frameskip_ptr = PLACEHOLDER_ADDR,
    // .g_run_file_size_ptr = PLACEHOLDER_ADDR,
    .gp_buf_64m_ptr = PLACEHOLDER_ADDR,
    .PINMUXL_ptr = PLACEHOLDER_ADDR,
    .PINMUXT_ptr = PLACEHOLDER_ADDR,
    .GPIOLCTRL_ptr = PLACEHOLDER_ADDR,
    .GPIOTCTRL_ptr = PLACEHOLDER_ADDR,
};

// Call this at startup. Pass 0 for SF2000, 1 for GB300.
void patch_hal_api(int platform) {
    if (platform == PLATFORM_SF2000) {
        // SF2000 addresses
        g_hal_api.fs_open = (void*)0x802a5a0c;
        g_hal_api.fs_close = (void*)0x802a6188;
        g_hal_api.fs_lseek = (void*)0x802a6048;
        g_hal_api.fs_read = (void*)0x802a5e04;
        g_hal_api.fs_write = (void*)0x802a5f28;
        g_hal_api.fs_access = (void*)0x802a5c9c;
        g_hal_api.fs_stat = (void*)0x802a5d58;
        g_hal_api.fs_fstat = (void*)0x802a5d34;
        g_hal_api.fs_sync = (void*)0x802a58e4;
        g_hal_api.fs_mkdir = (void*)0x802a5b68;
        g_hal_api.fs_opendir = (void*)0x802a5adc;
        g_hal_api.fs_closedir = (void*)0x802a61a4;
        g_hal_api.fs_readdir = (void*)0x802a60ec;
        g_hal_api.osal_tds2_cache_flush = (void*)0x80049214;
        g_hal_api.os_disable_interrupt = (void*)0x802da404;
        g_hal_api.os_enable_interrupt = (void*)0x802da42c;
        g_hal_api.dly_tsk = (void*)0x80309134;
        g_hal_api.os_get_tick_count = (void*)0x80309b7c;
        g_hal_api.dev_get_by_id = (void*)0x802730b0;
        g_hal_api.run_emulator = (void*)0x803589a4;
        g_hal_api.run_gba = (void*)0x80359d1c;
        g_hal_api.retro_video_refresh_cb = (void*)0x803583a8;
        g_hal_api.retro_audio_sample_batch_cb = (void*)0x80358430;
        g_hal_api.retro_input_poll_cb = (void*)0x80358688;
        g_hal_api.retro_input_state_cb = (void*)0x80358778;
        g_hal_api.retro_environment_cb = (void*)0x803587bc;
        g_hal_api.get_vp_init_low_lcd_para = (void*)0x801b9d0c;
        g_hal_api.switch_lcd_or_tv = (void*)0x801b9dd0;
        g_hal_api.vpo_ioctl = (void*)0x80271314;
        g_hal_api.osddrv_open = (void*)0x802719c8;
        g_hal_api.osddrv_close = (void*)0x80271aa8;
        g_hal_api.osddrv_3x_create_region = (void*)0x802721bc;
        g_hal_api.osddrv_3x_region_write = (void*)0x80272ab4;
        g_hal_api.osddrv_scale = (void*)0x80272dd8;
        g_hal_api.st7789v_caset_raset = (void*)0x8029a69c;
        g_hal_api.st7789v_ramwr = (void*)0x8029a740;
        g_hal_api.run_osd_region_write = (void*)0x80355fdc;
        g_hal_api.run_screen_write = (void*)0x80356058;
        g_hal_api.run_sound_advance = (void*)0x80356168;
        g_hal_api.RAMSIZE_ptr = (void*)0x80c09bdc;
        g_hal_api.g_errno_ptr = (void*)0x80c0a3b0;
        g_hal_api.g_snd_task_flags_ptr = (void*)0x80c0b574;
        g_hal_api.g_retro_game_info_ptr = (void*)0x80c0b678;
        g_hal_api.gfn_state_load_ptr = (void*)0x80c107cc;
        g_hal_api.gfn_state_save_ptr = (void*)0x80c1081c;
        g_hal_api.gfn_retro_get_region_ptr = (void*)0x80c107f8;
        g_hal_api.gfn_get_system_av_info_ptr = (void*)0x80c10808;
        g_hal_api.gfn_retro_load_game_ptr = (void*)0x80c10828;
        g_hal_api.gfn_retro_unload_game_ptr = (void*)0x80c10830;
        g_hal_api.gfn_retro_run_ptr = (void*)0x80c10840;
        g_hal_api.gfn_frameskip_ptr = (void*)0x80c1083c;
        // g_hal_api.g_run_file_size_ptr = (void*)0x80c107d8;
        g_hal_api.gp_buf_64m_ptr = (void*)0x80c10834;
        g_hal_api.PINMUXL_ptr = (void*)0xb88004a0;
        g_hal_api.PINMUXT_ptr = (void*)0xb8800500;
        g_hal_api.GPIOLCTRL_ptr = (void*)0xb8800044;
        g_hal_api.GPIOTCTRL_ptr = (void*)0xb8800344;
        
        // Set global variable pointers for SF2000
        // Patch the global variables to point to the correct firmware locations
        RAMSIZE = *(g_hal_api.RAMSIZE_ptr);
        g_errno = g_hal_api.g_errno_ptr;
        g_snd_task_flags = *(g_hal_api.g_snd_task_flags_ptr);
        g_retro_game_info = *(g_hal_api.g_retro_game_info_ptr);
        gfn_state_load = *(g_hal_api.gfn_state_load_ptr);
        gfn_state_save = *(g_hal_api.gfn_state_save_ptr);
        gfn_retro_get_region = *(g_hal_api.gfn_retro_get_region_ptr);
        gfn_get_system_av_info = *(g_hal_api.gfn_get_system_av_info_ptr);
        gfn_retro_load_game = *(g_hal_api.gfn_retro_load_game_ptr);
        gfn_retro_unload_game = *(g_hal_api.gfn_retro_unload_game_ptr);
        gfn_retro_run = *(g_hal_api.gfn_retro_run_ptr);
        gfn_frameskip = *(g_hal_api.gfn_frameskip_ptr);
        // *(unsigned*)&g_run_file_size = *(g_hal_api.g_run_file_size_ptr);
        gp_buf_64m = *(g_hal_api.gp_buf_64m_ptr);
        g_mxmv_screen_magic = 0x60; // Magic value for screen mirroring
        PINMUXL = g_hal_api.PINMUXL_ptr;
        PINMUXT = g_hal_api.PINMUXT_ptr;
        GPIOLCTRL = g_hal_api.GPIOLCTRL_ptr;
        GPIOTCTRL = g_hal_api.GPIOTCTRL_ptr;
        fw_fps_counter_enable = (int *)0x80c0b5e0;
        fw_fps_counter = (int *)0x80c0b5dc;
        fw_fps_counter_format = (char *)0x8099bdf0; // "%2d/%2d"
    } else if (platform == PLATFORM_GB300v1) {
        // GB300 addresses
        g_hal_api.fs_open = (void*)0x8025b78c;
        g_hal_api.fs_close = (void*)0x8025bf08;
        g_hal_api.fs_lseek = (void*)0x8025bdc8;
        g_hal_api.fs_read = (void*)0x8025bb84;
        g_hal_api.fs_write = (void*)0x8025bca8;
        g_hal_api.fs_access = (void*)0x8025ba1c;
        g_hal_api.fs_stat = (void*)0x8025bad8;
        g_hal_api.fs_fstat = (void*)0x8025bab4;
        g_hal_api.fs_sync = (void*)0x8025b664;
        g_hal_api.fs_mkdir = (void*)0x8025b8e8;
        g_hal_api.fs_opendir = (void*)0x8025b85c;
        g_hal_api.fs_closedir = (void*)0x8025bf24;
        g_hal_api.fs_readdir = (void*)0x8025be6c;
        g_hal_api.osal_tds2_cache_flush = (void*)0x80049214;
        g_hal_api.os_disable_interrupt = (void*)0x802901cc;
        g_hal_api.os_enable_interrupt = (void*)0x802901f4;
        g_hal_api.dly_tsk = (void*)0x802beefc;
        g_hal_api.os_get_tick_count = (void*)0x802bf944;
        g_hal_api.dev_get_by_id = (void*)0x80228e30;
        g_hal_api.run_emulator = (void*)0x8030d008;
        g_hal_api.run_gba = (void*)0x8030e4bc;
        g_hal_api.retro_video_refresh_cb = (void*)0x8030c960;
        g_hal_api.retro_audio_sample_batch_cb = (void*)0x8030c9e8;
        g_hal_api.retro_input_poll_cb = (void*)0x8030cc20;
        g_hal_api.retro_input_state_cb = (void*)0x8030cd10;
        g_hal_api.retro_environment_cb = (void*)0x8030cd54;
        g_hal_api.get_vp_init_low_lcd_para = (void*)0x8016fa38;
        g_hal_api.switch_lcd_or_tv = (void*)0x8016fafc;
        g_hal_api.vpo_ioctl = (void*)0x80227094;
        g_hal_api.osddrv_open = (void*)0x80227748;
        g_hal_api.osddrv_close = (void*)0x80227828;
        g_hal_api.osddrv_3x_create_region = (void*)0x80227f3c;
        g_hal_api.osddrv_3x_region_write = (void*)0x80228834;
        g_hal_api.osddrv_scale = (void*)0x80228b58;
        g_hal_api.st7789v_caset_raset = (void*)0x8025041c;
        g_hal_api.st7789v_ramwr = (void*)0x802504c0;
        g_hal_api.run_osd_region_write = (void*)0x8030b58c;
        g_hal_api.run_screen_write = (void*)0x8030b608;
        g_hal_api.run_sound_advance = (void*)0x8030b718;
        g_hal_api.RAMSIZE_ptr = (void*)0x806f5e84;
        g_hal_api.g_errno_ptr = (void*)0x806f6470;
        g_hal_api.g_snd_task_flags_ptr = (void*)0x806f7634;
        g_hal_api.g_retro_game_info_ptr = (void*)0x80ad8e18;
        g_hal_api.gfn_state_load_ptr = (void*)0x806f8fac;
        g_hal_api.gfn_state_save_ptr = (void*)0x806f9008;
        g_hal_api.gfn_retro_get_region_ptr = (void*)0x806f8fe4;
        g_hal_api.gfn_get_system_av_info_ptr = (void*)0x806f8ff4;
        g_hal_api.gfn_retro_load_game_ptr = (void*)0x806f9014;
        g_hal_api.gfn_retro_unload_game_ptr = (void*)0x806f901c;
        g_hal_api.gfn_retro_run_ptr = (void*)0x806f902c;
        g_hal_api.gfn_frameskip_ptr = (void*)0x806f9028;
        // g_hal_api.g_run_file_size_ptr = (void*)0x806f8e9c;
        g_hal_api.gp_buf_64m_ptr = (void*)0x806f9020;
        g_hal_api.PINMUXL_ptr = (void*)0xb88004a0;
        g_hal_api.PINMUXT_ptr = (void*)0xb8800500;
        g_hal_api.GPIOLCTRL_ptr = (void*)0xb8800044;
        g_hal_api.GPIOTCTRL_ptr = (void*)0xb8800344;
        
        // Set global variable pointers for GB300
        // Patch the global variables to point to the correct firmware locations
        RAMSIZE = *(g_hal_api.RAMSIZE_ptr);
        g_errno = g_hal_api.g_errno_ptr;
        g_snd_task_flags = *(g_hal_api.g_snd_task_flags_ptr);
        g_retro_game_info = *(g_hal_api.g_retro_game_info_ptr);
        gfn_state_load = *(g_hal_api.gfn_state_load_ptr);
        gfn_state_save = *(g_hal_api.gfn_state_save_ptr);
        gfn_retro_get_region = *(g_hal_api.gfn_retro_get_region_ptr);
        gfn_get_system_av_info = *(g_hal_api.gfn_get_system_av_info_ptr);
        gfn_retro_load_game = *(g_hal_api.gfn_retro_load_game_ptr);
        gfn_retro_unload_game = *(g_hal_api.gfn_retro_unload_game_ptr);
        gfn_retro_run = *(g_hal_api.gfn_retro_run_ptr);
        gfn_frameskip = *(g_hal_api.gfn_frameskip_ptr);
        // *(unsigned*)&g_run_file_size = *(g_hal_api.g_run_file_size_ptr);
        gp_buf_64m = *(g_hal_api.gp_buf_64m_ptr);
        g_mxmv_screen_magic = 0x28; // Magic value for screen mirroring
        PINMUXL = g_hal_api.PINMUXL_ptr;
        PINMUXT = g_hal_api.PINMUXT_ptr;
        GPIOLCTRL = g_hal_api.GPIOLCTRL_ptr;
        GPIOTCTRL = g_hal_api.GPIOTCTRL_ptr;
        fw_fps_counter_enable = (int *)0x806f7698;
        fw_fps_counter = (int *)0x806f7694;
        fw_fps_counter_format = (char *)0x806674a0; // "%2d/%2d"
    } else { // Unknown
        g_hal_api.fs_open = (void*)0xdeadc0de;
        g_hal_api.fs_close = (void*)0xdeadc0de;
        g_hal_api.fs_lseek = (void*)0xdeadc0de;
        g_hal_api.fs_read = (void*)0xdeadc0de;
        g_hal_api.fs_write = (void*)0xdeadc0de;
        g_hal_api.fs_access = (void*)0xdeadc0de;
        g_hal_api.fs_stat = (void*)0xdeadc0de;
        g_hal_api.fs_fstat = (void*)0xdeadc0de;
        g_hal_api.fs_sync = (void*)0xdeadc0de;
        g_hal_api.fs_mkdir = (void*)0xdeadc0de;
        g_hal_api.fs_opendir = (void*)0xdeadc0de;
        g_hal_api.fs_closedir = (void*)0xdeadc0de;
        g_hal_api.fs_readdir = (void*)0xdeadc0de;
        g_hal_api.osal_tds2_cache_flush = (void*)0xdeadc0de;
        g_hal_api.os_disable_interrupt = (void*)0xdeadc0de;
        g_hal_api.os_enable_interrupt = (void*)0xdeadc0de;
        g_hal_api.dly_tsk = (void*)0xdeadc0de;
        g_hal_api.os_get_tick_count = (void*)0xdeadc0de;
        g_hal_api.dev_get_by_id = (void*)0xdeadc0de;
        g_hal_api.run_emulator = (void*)0xdeadc0de;
        g_hal_api.run_gba = (void*)0xdeadc0de;
        g_hal_api.retro_video_refresh_cb = (void*)0xdeadc0de;
        g_hal_api.retro_audio_sample_batch_cb = (void*)0xdeadc0de;
        g_hal_api.retro_input_poll_cb = (void*)0xdeadc0de;
        g_hal_api.retro_input_state_cb = (void*)0xdeadc0de;
        g_hal_api.retro_environment_cb = (void*)0xdeadc0de;
        g_hal_api.get_vp_init_low_lcd_para = (void*)0xdeadc0de;
        g_hal_api.switch_lcd_or_tv = (void*)0xdeadc0de;
        g_hal_api.vpo_ioctl = (void*)0xdeadc0de;
        g_hal_api.osddrv_open = (void*)0xdeadc0de;
        g_hal_api.osddrv_close = (void*)0xdeadc0de;
        g_hal_api.osddrv_3x_create_region = (void*)0xdeadc0de;
        g_hal_api.osddrv_3x_region_write = (void*)0xdeadc0de;
        g_hal_api.osddrv_scale = (void*)0xdeadc0de;
        g_hal_api.st7789v_caset_raset = (void*)0xdeadc0de;
        g_hal_api.st7789v_ramwr = (void*)0xdeadc0de;
        g_hal_api.run_osd_region_write = (void*)0xdeadc0de;
        g_hal_api.run_screen_write = (void*)0xdeadc0de;
        g_hal_api.run_sound_advance = (void*)0xdeadc0de;
        g_hal_api.RAMSIZE_ptr = (void*)0xdeadc0de;
        g_hal_api.g_errno_ptr = (void*)0xdeadc0de;
        g_hal_api.g_snd_task_flags_ptr = (void*)0xdeadc0de;
        g_hal_api.g_retro_game_info_ptr = (void*)0xdeadc0de;
        g_hal_api.gfn_state_load_ptr = (void*)0xdeadc0de;
        g_hal_api.gfn_state_save_ptr = (void*)0xdeadc0de;
        g_hal_api.gfn_retro_get_region_ptr = (void*)0xdeadc0de;
        g_hal_api.gfn_get_system_av_info_ptr = (void*)0xdeadc0de;
        g_hal_api.gfn_retro_load_game_ptr = (void*)0xdeadc0de;
        g_hal_api.gfn_retro_unload_game_ptr = (void*)0xdeadc0de;
        g_hal_api.gfn_retro_run_ptr = (void*)0xdeadc0de;
        g_hal_api.gfn_frameskip_ptr = (void*)0xdeadc0de;
        // g_hal_api.g_run_file_size_ptr = (void*)0xdeadc0de;
        g_hal_api.gp_buf_64m_ptr = (void*)0xdeadc0de;
        g_hal_api.PINMUXL_ptr = (void*)0xdeadc0de;
        g_hal_api.PINMUXT_ptr = (void*)0xdeadc0de;
        g_hal_api.GPIOLCTRL_ptr = (void*)0xdeadc0de;
        g_hal_api.GPIOTCTRL_ptr = (void*)0xdeadc0de;
    }
}

// File system function implementations
int fs_open(const char *path, int oflag, int perms) {
    return g_hal_api.fs_open(path, oflag, perms);
}

int fs_close(int fd) {
    return g_hal_api.fs_close(fd);
}

int64_t fs_lseek(int fd, int64_t offset, int whence) {
    return g_hal_api.fs_lseek(fd, offset, whence);
}

ssize_t fs_read(int fd, void *buf, size_t nbyte) {
    return g_hal_api.fs_read(fd, buf, nbyte);
}

ssize_t fs_write(int fd, const void *buf, size_t nbyte) {
    return g_hal_api.fs_write(fd, buf, nbyte);
}

int fs_access(const char *path, int mode) {
    return g_hal_api.fs_access(path, mode);
}

int fs_stat(const char *path, void *sbuf) {
    return g_hal_api.fs_stat(path, sbuf);
}

int fs_fstat(int fd, void *sbuf) {
    return g_hal_api.fs_fstat(fd, sbuf);
}

int fs_sync(const char *path) {
    return g_hal_api.fs_sync(path);
}

int fs_mkdir(const char *path, int mode) {
    return g_hal_api.fs_mkdir(path, mode);
}

int fs_opendir(const char *path) {
    return g_hal_api.fs_opendir(path);
}

int fs_closedir(int fd) {
    return g_hal_api.fs_closedir(fd);
}

ssize_t fs_readdir(int fd, void *buffer) {
    return g_hal_api.fs_readdir(fd, buffer);
}

// OS function implementations
void osal_tds2_cache_flush(void *buf, unsigned sz) {
    g_hal_api.osal_tds2_cache_flush(buf, sz);
}

void os_disable_interrupt(void) {
    g_hal_api.os_disable_interrupt();
}

void os_enable_interrupt(void) {
    g_hal_api.os_enable_interrupt();
}

int dly_tsk(unsigned ms) {
    return g_hal_api.dly_tsk(ms);
}

uint32_t os_get_tick_count(void) {
    return g_hal_api.os_get_tick_count();
}

// Device function implementations
HANDLE dev_get_by_id(uint32_t a, uint16_t b) {
    return g_hal_api.dev_get_by_id(a, b);
}

// Emulator function implementations
int run_emulator(int load_state) {
    return g_hal_api.run_emulator(load_state);
}

void run_gba(const char *filename, int load_state) {
    g_hal_api.run_gba(filename, load_state);
}

// Libretro callback implementations
void retro_video_refresh_cb(const void *data, unsigned width, unsigned height, size_t pitch) {
    g_hal_api.retro_video_refresh_cb(data, width, height, pitch);
}

size_t retro_audio_sample_batch_cb(const int16_t *data, size_t frames) {
    return g_hal_api.retro_audio_sample_batch_cb(data, frames);
}

void retro_input_poll_cb(void) {
    g_hal_api.retro_input_poll_cb();
}

int16_t retro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id) {
    return g_hal_api.retro_input_state_cb(port, device, index, id);
}

bool retro_environment_cb(unsigned cmd, void *data) {
    return g_hal_api.retro_environment_cb(cmd, data);
}

// Driver function implementations
void *get_vp_init_low_lcd_para(void) {
    return g_hal_api.get_vp_init_low_lcd_para();
}

void switch_lcd_or_tv(int mode) {
    g_hal_api.switch_lcd_or_tv(mode);
}

int vpo_ioctl(int cmd, void *arg) {
    return g_hal_api.vpo_ioctl(cmd, arg);
}

int osddrv_open(void) {
    return g_hal_api.osddrv_open();
}

int osddrv_close(void) {
    return g_hal_api.osddrv_close();
}

int osddrv_3x_create_region(void *params) {
    return g_hal_api.osddrv_3x_create_region(params);
}

int osddrv_3x_region_write(void *params) {
    return g_hal_api.osddrv_3x_region_write(params);
}

int osddrv_scale(void *params) {
    return g_hal_api.osddrv_scale(params);
}

void st7789v_caset_raset(int x1, int y1, int x2, int y2) {
    g_hal_api.st7789v_caset_raset(x1, y1, x2, y2);
}

void st7789v_ramwr(void) {
    g_hal_api.st7789v_ramwr();
}

// Libretro frontend function implementations
void run_osd_region_write(void *params) {
    g_hal_api.run_osd_region_write(params);
}

void run_screen_write(void *params) {
    g_hal_api.run_screen_write(params);
}

void run_sound_advance(void) {
    g_hal_api.run_sound_advance();
}

// Global variable definitions that point to the HAL API
// These variables are declared as extern in stockfw.h, so we need to provide definitions
unsigned RAMSIZE;
int *g_errno = NULL;
int g_snd_task_flags;
struct retro_game_info g_retro_game_info;
int (*gfn_state_load)(const char *);
int (*gfn_state_save)(const char *);
unsigned (*gfn_retro_get_region)(void);
void (*gfn_get_system_av_info)(struct retro_system_av_info *info);
bool (*gfn_retro_load_game)(const struct retro_game_info *game);
void (*gfn_retro_unload_game)(void);
void (*gfn_retro_run)(void);
void (*gfn_frameskip)(BOOL flag);
// const unsigned g_run_file_size;
void *gp_buf_64m;

// Hardware register pointers
volatile uint32_t *PINMUXL = NULL;
volatile uint32_t *PINMUXT = NULL;
volatile uint32_t *GPIOLCTRL = NULL;
volatile uint32_t *GPIOTCTRL = NULL;

void restore_stock_gp(int platform) {
    // https://gitlab.com/kobily/sf2000_multicore/-/commit/328bce4173316a6ea0afe4c360ee4f3d5b951c19 condensed to core's side
	// Before calling "irq_handler", make sure the $gp register points to the original address that
	// was initially set by the stock startup code and that all stock code expect it to be.
	//
	// This solves the freeze that was caused when using gpSP dynarec.
	// The dynamically generated code modifies the $gp register for the duration of its execution,
	// but if suddenly an interrupt occurs and it needs to access some global vars, then the system will crash
	// or freeze because $gp doesn't have right value that the irq/interrupt handlers expect it to be.
	os_disable_interrupt();
	
    if (platform == PLATFORM_SF2000) {
        *(unsigned *)0x80049744 = 0x3c1c80c1; // lui$gp, 0x80c1
	    *(unsigned *)0x80049748 = 0x279c14f4; // addiu$gp, 0x14f4
    } else if (platform == PLATFORM_GB300v1) {
        *(unsigned *)0x80049744 = 0x3c1c8070; // lui$gp, 0x8070
	    *(unsigned *)0x80049748 = 0x279cd798; // addiu$gp, 0xd798
    } else {
        // Unknown platform, do nothing
    }

    __builtin___clear_cache((void *)0x80049744, (void *)0x8004974c);
    os_enable_interrupt();
}

// Commented code below, just because I may use this in the
// future for other purpose.

// MIPS instruction macros for patching jump instructions
// #define MIPS_J(pfunc)    (2 << 26) | (uint32_t)pfunc >> 2 & ((1 << 26) - 1)
// #define MIPS_JAL(pfunc)  (3 << 26) | (uint32_t)pfunc >> 2 & ((1 << 26) - 1)

// Patch macros for replacing function calls with jumps
// #define PATCH_J(target, hook)    *(uint32_t*)(target) = MIPS_J(hook)
// #define PATCH_JAL(target, hook)  *(uint32_t*)(target) = MIPS_JAL(hook)

// static void restore_stock_gp()
// {
// 	// set $gp to the original stock's value like is done at 0x80001274 where $gp is
// 	// initially set by the stock startup code
// 	asm(
//         "lui	$gp, 0x80c1				\n"
//         "addiu	$gp, $gp, 0x14f4		\n"
//     );
// }

// PATCH_JAL(0x80049744, restore_stock_gp);
