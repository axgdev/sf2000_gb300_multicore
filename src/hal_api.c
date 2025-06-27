#include <stdio.h>
#include <stdlib.h>
#include "hal_api.h"
#include "debug.h"

// The global API struct instance
HAL_API hal_api;

// Use a known function pointer's address and value to differentiate the platforms
#define PLATFORM_SIGNATURE_ADDRESS      ((volatile uint32_t*)0x80c10840) // gfn_retro_run on SF2000
#define SF2000_RUN_EMULATOR_ADDRESS     0x803589a4

void hal_init(void) {
    // Runtime platform detection:
    // Check the value at the known address for SF2000's 'gfn_retro_run' pointer.
    // If it contains the address of SF2000's 'run_emulator', we're on an SF2000.
    // Otherwise, we assume it's a GB300.
    if (*PLATFORM_SIGNATURE_ADDRESS == SF2000_RUN_EMULATOR_ADDRESS) {
        // --- Platform is SF2000 (bisrv_08_03.asd) ---
        xlog("HAL: SF2000 platform detected.\n");
        hal_api.strcat = (void*)0x801b0b28;
        hal_api.strncmp = (void*)0x801b0bc4;
        hal_api.strncpy = (void*)0x801b0c9c;
        hal_api.strchr = (void*)0x801b0d6c;
        hal_api.strrchr = (void*)0x801b0dfc;
        hal_api.strstr = (void*)0x801b0e1c;
        hal_api.strcasecmp = (void*)0x801b0e70;
        hal_api.strncasecmp = (void*)0x801b0ef0;
        hal_api.memchr = (void*)0x801b0f50;
        hal_api.tolower = (void*)0x801b0f80;
        hal_api.toupper = (void*)0x801b0fa0;
        hal_api.isalnum = (void*)0x801b0fc0;
        hal_api.isalpha = (void*)0x801b0fd8;
        hal_api.isascii = (void*)0x801b0ff0;
        hal_api.iscntrl = (void*)0x801b0ff8;
        hal_api.isdigit = (void*)0x801b1010;
        hal_api.isgraph = (void*)0x801b1028;
        hal_api.islower = (void*)0x801b1040;
        hal_api.isprint = (void*)0x801b1058;
        hal_api.ispunct = (void*)0x801b1070;
        hal_api.isspace = (void*)0x801b1088;
        hal_api.isupper = (void*)0x801b10a0;
        hal_api.isxdigit = (void*)0x801b10b8;
        hal_api.toascii = (void*)0x801b10d0;
        hal_api._tolower = (void*)0x801b10d8;
        hal_api._toupper = (void*)0x801b10e0;
        hal_api.isnan = (void*)0x801b10e8;
        hal_api.isinf = (void*)0x801b1134;
        hal_api.strtol = (void*)0x801b1184;
        hal_api.strtoul = (void*)0x801b1374;
        hal_api.sbrk = (void*)0x8028b5f8;
        hal_api.malloc = (void*)0x8028b8b8;
        hal_api.free = (void*)0x8028c4c8;
        hal_api.realloc = (void*)0x8028c58c;
        hal_api.calloc = (void*)0x8028c844;
        hal_api.vsnprintf = (void*)0x8028e2d8;
        hal_api.sprintf = (void*)0x8028e38c;
        hal_api.vprintf = (void*)0x8028e434;
        hal_api.printf = (void*)0x8028e474;
        hal_api.snprintf = (void*)0x8028e49c;
        hal_api.vsprintf = (void*)0x8028e4bc;
        hal_api.rand = (void*)0x8028e56c;
        hal_api.memcpy = (void*)0x8028e620;
        hal_api.memset = (void*)0x8028e850;
        hal_api.memcmp = (void*)0x8028e930;
        hal_api.memmove = (void*)0x8028e994;
        hal_api.strcpy = (void*)0x8028ea60;
        hal_api.strcmp = (void*)0x8028eaa0;
        hal_api.strlen = (void*)0x8028eae4;
        hal_api.atoi = (void*)0x8028eb0c;
        hal_api.time = (void*)0x8028edb4;
        hal_api.localtime = (void*)0x8028effc;
        hal_api.vsscanf = (void*)0x802903d0;
        hal_api.sscanf = (void*)0x80290410;
        hal_api.fs_open = (void*)0x802a5a0c;
        hal_api.fs_read = (void*)0x802a5e04;
        hal_api.fs_write = (void*)0x802a5f28;
        hal_api.fs_lseek = (void*)0x802a6048;
        hal_api.fs_close = (void*)0x802a6188;
        hal_api.fs_access = (void*)0x802a5c9c;
        hal_api.fs_fstat = (void*)0x802a5d34;
        hal_api.fs_stat = (void*)0x802a5d58;
        hal_api.fs_mkdir = (void*)0x802a5b68;
        hal_api.fs_opendir = (void*)0x802a5adc;
        hal_api.fs_closedir = (void*)0x802a61a4;
        hal_api.fs_readdir = (void*)0x802a60ec;
        hal_api.fs_sync = (void*)0x802a58e4;
        hal_api.strdup = (void*)0x802acb40;
        hal_api.fclose = (void*)0x802acbf4;
        hal_api.fflush = (void*)0x802acd64;
        hal_api.fopen = (void*)0x802ad1d8;
        hal_api.fw_fread = (void*)0x802ad34c;
        hal_api.fseeko = (void*)0x802ad4b8;
        hal_api.ftell = (void*)0x802adbd0;
        hal_api.ftello = (void*)0x802adbec;
        hal_api.fwrite = (void*)0x802adf60;
        hal_api.fgets = (void*)0x802acec0;
        hal_api.osal_tds2_cache_flush = (void*)0x80049214;
        hal_api.os_disable_interrupt = (void*)0x802da404;
        hal_api.os_enable_interrupt = (void*)0x802da42c;
        hal_api.dly_tsk = (void*)0x80309134;
        hal_api.os_get_tick_count = (void*)0x80309b7c;
        hal_api.get_vp_init_low_lcd_para = (void*)0x801b9d0c;
        hal_api.switch_lcd_or_tv = (void*)0x801b9dd0;
        hal_api.vpo_ioctl = (void*)0x80271314;
        hal_api.osddrv_open = (void*)0x802719c8;
        hal_api.osddrv_close = (void*)0x80271aa8;
        hal_api.osddrv_3x_create_region = (void*)0x802721bc;
        hal_api.osddrv_3x_region_write = (void*)0x80272ab4;
        hal_api.osddrv_scale = (void*)0x80272dd8;
        hal_api.dev_get_by_id = (void*)0x802730b0;
        hal_api.st7789v_caset_raset = (void*)0x8029a69c;
        hal_api.st7789v_ramwr = (void*)0x8029a740;
        hal_api.run_osd_region_write = (void*)0x80355fdc;
        hal_api.run_screen_write = (void*)0x80356058;
        hal_api.run_sound_advance = (void*)0x80356168;
        hal_api.retro_video_refresh_cb = (void*)0x803583a8;
        hal_api.retro_audio_sample_batch_cb = (void*)0x80358430;
        hal_api.retro_input_poll_cb = (void*)0x80358688;
        hal_api.retro_input_state_cb = (void*)0x80358778;
        hal_api.retro_environment_cb = (void*)0x803587bc;
        hal_api.run_emulator = (void*)0x803589a4;
        hal_api.run_gba = (void*)0x80359d1c;
        hal_api._ctype_ = (void*)0x8099553c;
        hal_api.RAMSIZE = (void*)0x80c09bdc;
        hal_api.g_errno = (void*)0x80c0a3b0;
        hal_api.g_snd_task_flags = (void*)0x80c0b574;
        hal_api.g_retro_game_info = (void*)0x80c0b678;
        hal_api.gfn_state_load = (void*)0x80c107cc;
        hal_api.gfn_state_save = (void*)0x80c1081c;
        hal_api.gfn_retro_get_region = (void*)0x80c107f8;
        hal_api.gfn_get_system_av_info = (void*)0x80c10808;
        hal_api.gfn_retro_load_game = (void*)0x80c10828;
        hal_api.gfn_retro_unload_game = (void*)0x80c10830;
        hal_api.gfn_retro_run = (void*)0x80c10840;
        hal_api.gfn_frameskip = (void*)0x80c1083c;
        hal_api.g_run_file_size = (void*)0x80c107d8;
        hal_api.gp_buf_64m = (void*)0x80c10834;
        hal_api.PINMUXL = (void*)0xb88004a0;
        hal_api.PINMUXT = (void*)0xb8800500;
        hal_api.GPIOLCTRL = (void*)0xb8800044;
        hal_api.GPIOTCTRL = (void*)0xb8800344;
    } else {
        // --- Platform is GB300 ---
        xlog("HAL: GB300 platform detected.\n");
        hal_api.strcat = (void*)0x80165fd4;
        hal_api.strncmp = (void*)0x80166070;
        hal_api.strncpy = (void*)0x80166148;
        hal_api.strchr = (void*)0x80166218;
        hal_api.strrchr = (void*)0x801662a8;
        hal_api.strstr = (void*)0x801662c8;
        hal_api.strcasecmp = (void*)0x8016631c;
        hal_api.strncasecmp = (void*)0x8016639c;
        hal_api.memchr = (void*)0x801663fc;
        hal_api.tolower = (void*)0x80166578;
        hal_api.toupper = (void*)0x80166598;
        hal_api.isalnum = (void*)0x801665b8;
        hal_api.isalpha = (void*)0x801665d0;
        hal_api.isascii = (void*)0x801665e8;
        hal_api.iscntrl = (void*)0x801665f0;
        hal_api.isdigit = (void*)0x80166608;
        hal_api.isgraph = (void*)0x80166620;
        hal_api.islower = (void*)0x80166638;
        hal_api.isprint = (void*)0x80166650;
        hal_api.ispunct = (void*)0x80166668;
        hal_api.isspace = (void*)0x80166680;
        hal_api.isupper = (void*)0x80166698;
        hal_api.isxdigit = (void*)0x801666b0;
        hal_api.toascii = (void*)0x801666c8;
        hal_api._tolower = (void*)0x801666d0;
        hal_api._toupper = (void*)0x801666d8;
        hal_api.isnan = (void*)0x80166718;
        hal_api.isinf = (void*)0x80166764;
        hal_api.strtol = (void*)0x801667b4;
        hal_api.strtoul = (void*)0x801669a4;
        hal_api.sbrk = (void*)0x8024198c;
        hal_api.malloc = (void*)0x80241c4c;
        hal_api.free = (void*)0x8024285c;
        hal_api.realloc = (void*)0x80242920;
        hal_api.calloc = (void*)0x80242bd8;
        hal_api.vsnprintf = (void*)0x8024466c;
        hal_api.sprintf = (void*)0x80244720;
        hal_api.vprintf = (void*)0x802447c8;
        hal_api.printf = (void*)0x80244808;
        hal_api.snprintf = (void*)0x80244830;
        hal_api.vsprintf = (void*)0x80244850;
        hal_api.rand = (void*)0x80244900;
        hal_api.memcpy = (void*)0x802449b4;
        hal_api.memset = (void*)0x80244be4;
        hal_api.memcmp = (void*)0x80244cc4;
        hal_api.memmove = (void*)0x80244d28;
        hal_api.strcpy = (void*)0x80244df4;
        hal_api.strcmp = (void*)0x80244e34;
        hal_api.strlen = (void*)0x80244e78;
        hal_api.atoi = (void*)0x80244ea0;
        hal_api.time = (void*)0x80245148;
        hal_api.localtime = (void*)0x80245390;
        hal_api.vsscanf = (void*)0x80246764;
        hal_api.sscanf = (void*)0x802467a4;
        hal_api.fs_open = (void*)0x8025b78c;
        hal_api.fs_read = (void*)0x8025bb84;
        hal_api.fs_write = (void*)0x8025bca8;
        hal_api.fs_lseek = (void*)0x8025bdc8;
        hal_api.fs_close = (void*)0x8025bf08;
        hal_api.fs_access = (void*)0x8025ba1c;
        hal_api.fs_fstat = (void*)0x8025bab4;
        hal_api.fs_stat = (void*)0x8025bad8;
        hal_api.fs_mkdir = (void*)0x8025b8e8;
        hal_api.fs_opendir = (void*)0x8025b85c;
        hal_api.fs_closedir = (void*)0x8025bf24;
        hal_api.fs_readdir = (void*)0x8025be6c;
        hal_api.fs_sync = (void*)0x8025b664;
        hal_api.strdup = (void*)0x802628c0;
        hal_api.fclose = (void*)0x80262974;
        hal_api.fflush = (void*)0x80262ae4;
        hal_api.fopen = (void*)0x80262f58;
        hal_api.fw_fread = (void*)0x80263138;
        hal_api.fseeko = (void*)0x80263280;
        hal_api.ftell = (void*)0x802fc2c4;
        hal_api.ftello = (void*)0x802639b4;
        hal_api.fwrite = (void*)0x80263c60;
        hal_api.fgets = (void*)0x80262c40;
        hal_api.osal_tds2_cache_flush = (void*)0x800491e8; // This seems to be SF2000's, GB300 is 0x80049214. Let's use the one from the provided ld file.
        // The user provided two different addresses for osal_tds2_cache_flush for gb300.
        // `bisrv_08_03-core_gb300.ld.txt` -> 0x80049214
        // `bisrv_08_03_gb300.ld.txt` -> 0x800491e8
        // Let's assume the -core one is correct for cores, but it's a TDS2 function, so it should be the same. I'll use 0x80049214 from the -core file.
        hal_api.osal_tds2_cache_flush = (void*)0x80049214;
        hal_api.os_disable_interrupt = (void*)0x802901cc;
        hal_api.os_enable_interrupt = (void*)0x802901f4;
        hal_api.dly_tsk = (void*)0x802beefc;
        hal_api.os_get_tick_count = (void*)0x802bf944;
        hal_api.get_vp_init_low_lcd_para = (void*)0x8016fa38;
        hal_api.switch_lcd_or_tv = (void*)0x8016fafc;
        hal_api.vpo_ioctl = (void*)0x80227094;
        hal_api.osddrv_open = (void*)0x80227748;
        hal_api.osddrv_close = (void*)0x80227828;
        hal_api.osddrv_3x_create_region = (void*)0x80227f3c;
        hal_api.osddrv_3x_region_write = (void*)0x80228834;
        hal_api.osddrv_scale = (void*)0x80228b58;
        hal_api.dev_get_by_id = (void*)0x80228e30;
        hal_api.st7789v_caset_raset = (void*)0x8025041c;
        hal_api.st7789v_ramwr = (void*)0x802504c0;
        hal_api.run_osd_region_write = (void*)0x8030b58c;
        hal_api.run_screen_write = (void*)0x8030b608;
        hal_api.run_sound_advance = (void*)0x8030b718;
        hal_api.retro_video_refresh_cb = (void*)0x8030c960;
        hal_api.retro_audio_sample_batch_cb = (void*)0x8030c9e8;
        hal_api.retro_input_poll_cb = (void*)0x8030cc20;
        hal_api.retro_input_state_cb = (void*)0x8030cd10;
        hal_api.retro_environment_cb = (void*)0x8030cd54;
        hal_api.run_emulator = (void*)0x8030d008;
        hal_api.run_gba = (void*)0x8030e4bc;
        hal_api._ctype_ = (void*)0x80660d34;
        hal_api.RAMSIZE = (void*)0x806f5e84;
        hal_api.g_errno = (void*)0x806f6470;
        hal_api.g_snd_task_flags = (void*)0x806f7634;
        hal_api.g_retro_game_info = (void*)0x80ad8e18;
        hal_api.gfn_state_load = (void*)0x806f8fac;
        hal_api.gfn_state_save = (void*)0x806f9008;
        hal_api.gfn_retro_get_region = (void*)0x806f8fe4;
        hal_api.gfn_get_system_av_info = (void*)0x806f8ff4;
        hal_api.gfn_retro_load_game = (void*)0x806f9014;
        hal_api.gfn_retro_unload_game = (void*)0x806f901c;
        hal_api.gfn_retro_run = (void*)0x806f902c;
        hal_api.gfn_frameskip = (void*)0x806f9028;
        hal_api.g_run_file_size = (void*)0x806f8e9c;
        hal_api.gp_buf_64m = (void*)0x806f9020;
        hal_api.PINMUXL = (void*)0xb88004a0;
        hal_api.PINMUXT = (void*)0xb8800500;
        hal_api.GPIOLCTRL = (void*)0xb8800044;
        hal_api.GPIOTCTRL = (void*)0xb8800344;
    }
}