#include "hal.h"

stock_api_t g_stock_api;

#if defined(PLATFORM_SF2000)
#include "sf2000_addrs.h"
#elif defined(PLATFORM_GB300)
#include "gb300_addrs.h"
#else
#error "No platform defined"
#endif

void hal_init(void) {
    // libc functions
    g_stock_api.strcat = (void*)STRCAT_ADDR;
    g_stock_api.strncmp = (void*)STRNCMP_ADDR;
    g_stock_api.strncpy = (void*)STRNCPY_ADDR;
    g_stock_api.strchr = (void*)STRCHR_ADDR;
    g_stock_api.strrchr = (void*)STRRCHR_ADDR;
    g_stock_api.strstr = (void*)STRSTR_ADDR;
    g_stock_api.strcasecmp = (void*)STRCASECMP_ADDR;
    g_stock_api.strncasecmp = (void*)STRNCASECMP_ADDR;
    g_stock_api.memchr = (void*)MEMCHR_ADDR;
    g_stock_api.tolower = (void*)TOLOWER_ADDR;
    g_stock_api.toupper = (void*)TOUPPER_ADDR;
    g_stock_api.isalnum = (void*)ISALNUM_ADDR;
    g_stock_api.isalpha = (void*)ISALPHA_ADDR;
    g_stock_api.isascii = (void*)ISASCII_ADDR;
    g_stock_api.iscntrl = (void*)ISCNTRL_ADDR;
    g_stock_api.isdigit = (void*)ISDIGIT_ADDR;
    g_stock_api.isgraph = (void*)ISGRAPH_ADDR;
    g_stock_api.islower = (void*)ISLOWER_ADDR;
    g_stock_api.isprint = (void*)ISPRINT_ADDR;
    g_stock_api.ispunct = (void*)ISPUNCT_ADDR;
    g_stock_api.isspace = (void*)ISSPACE_ADDR;
    g_stock_api.isupper = (void*)ISUPPER_ADDR;
    g_stock_api.isxdigit = (void*)ISXDIGIT_ADDR;
    g_stock_api.toascii = (void*)TOASCII_ADDR;
    g_stock_api._tolower = (void*)_TOLOWER_ADDR;
    g_stock_api._toupper = (void*)_TOUPPER_ADDR;
    g_stock_api.isnan = (void*)ISNAN_ADDR;
    g_stock_api.isinf = (void*)ISINF_ADDR;
    g_stock_api.strtol = (void*)STRTOL_ADDR;
    g_stock_api.strtoul = (void*)STRTOUL_ADDR;
    g_stock_api.strtod = (void*)STRTOD_ADDR;
    g_stock_api.sbrk = (void*)SBRK_ADDR;
    g_stock_api.malloc = (void*)MALLOC_ADDR;
    g_stock_api.free = (void*)FREE_ADDR;
    g_stock_api.realloc = (void*)REALLOC_ADDR;
    g_stock_api.calloc = (void*)CALLOC_ADDR;
    g_stock_api.vsnprintf = (void*)VSNPRINTF_ADDR;
    g_stock_api.sprintf = (void*)SPRINTF_ADDR;
    g_stock_api.vprintf = (void*)VPRINTF_ADDR;
    g_stock_api.printf = (void*)PRINTF_ADDR;
    g_stock_api.snprintf = (void*)SNPRINTF_ADDR;
    g_stock_api.vsprintf = (void*)VSPRINTF_ADDR;
    g_stock_api.rand = (void*)RAND_ADDR;
    g_stock_api.memcpy = (void*)MEMCPY_ADDR;
    g_stock_api.memset = (void*)MEMSET_ADDR;
    g_stock_api.memcmp = (void*)MEMCMP_ADDR;
    g_stock_api.memmove = (void*)MEMMOVE_ADDR;
    g_stock_api.strcpy = (void*)STRCPY_ADDR;
    g_stock_api.strcmp = (void*)STRCMP_ADDR;
    g_stock_api.strlen = (void*)STRLEN_ADDR;
    g_stock_api.atoi = (void*)ATOI_ADDR;
    g_stock_api.time = (void*)TIME_ADDR;
    g_stock_api.localtime = (void*)LOCALTIME_ADDR;
    g_stock_api.vsscanf = (void*)VSSCANF_ADDR;
    g_stock_api.sscanf = (void*)SSCANF_ADDR;
    g_stock_api.open = (void*)OPEN_ADDR;
    g_stock_api.read = (void*)READ_ADDR;
    g_stock_api.write = (void*)WRITE_ADDR;
    g_stock_api.lseek = (void*)LSEEK_ADDR;
    g_stock_api.close = (void*)CLOSE_ADDR;
    g_stock_api.strdup = (void*)STRDUP_ADDR;
    g_stock_api.fclose = (void*)FCLOSE_ADDR;
    g_stock_api.fflush = (void*)FFLUSH_ADDR;
    g_stock_api.fopen = (void*)FOPEN_ADDR;
    g_stock_api.fw_fread = (void*)FW_FREAD_ADDR;
    g_stock_api.fseeko = (void*)FSEEKO_ADDR;
    g_stock_api.ftell = (void*)FTELL_ADDR;
    g_stock_api.ftello = (void*)FTELLO_ADDR;
    g_stock_api.fwrite = (void*)FWRITE_ADDR;
    g_stock_api.fgets = (void*)FGETS_ADDR;

    // Filesystem functions
    g_stock_api.fs_open = (void*)FS_OPEN_ADDR;
    g_stock_api.fs_close = (void*)FS_CLOSE_ADDR;
    g_stock_api.fs_lseek = (void*)FS_LSEEK_ADDR;
    g_stock_api.fs_read = (void*)FS_READ_ADDR;
    g_stock_api.fs_write = (void*)FS_WRITE_ADDR;
    g_stock_api.fs_access = (void*)FS_ACCESS_ADDR;
    g_stock_api.fs_stat = (void*)FS_STAT_ADDR;
    g_stock_api.fs_fstat = (void*)FS_FSTAT_ADDR;
    g_stock_api.fs_sync = (void*)FS_SYNC_ADDR;
    g_stock_api.fs_mkdir = (void*)FS_MKDIR_ADDR;
    g_stock_api.fs_opendir = (void*)FS_OPENDIR_ADDR;
    g_stock_api.fs_closedir = (void*)FS_CLOSEDIR_ADDR;
    g_stock_api.fs_readdir = (void*)FS_READDIR_ADDR;

    // TDS2 functions
    g_stock_api.osal_tds2_cache_flush = (void*)OSAL_TDS2_CACHE_FLUSH_ADDR;
    g_stock_api.os_disable_interrupt = (void*)OS_DISABLE_INTERRUPT_ADDR;
    g_stock_api.os_enable_interrupt = (void*)OS_ENABLE_INTERRUPT_ADDR;
    g_stock_api.dly_tsk = (void*)DLY_TSK_ADDR;
    g_stock_api.os_get_tick_count = (void*)OS_GET_TICK_COUNT_ADDR;

    // Driver functions
    g_stock_api.get_vp_init_low_lcd_para = (void*)GET_VP_INIT_LOW_LCD_PARA_ADDR;
    g_stock_api.switch_lcd_or_tv = (void*)SWITCH_LCD_OR_TV_ADDR;
    g_stock_api.vpo_ioctl = (void*)VPO_IOCTL_ADDR;
    g_stock_api.osddrv_open = (void*)OSDDRV_OPEN_ADDR;
    g_stock_api.osddrv_close = (void*)OSDDRV_CLOSE_ADDR;
    g_stock_api.osddrv_3x_create_region = (void*)OSDDRV_3X_CREATE_REGION_ADDR;
    g_stock_api.osddrv_3x_region_write = (void*)OSDDRV_3X_REGION_WRITE_ADDR;
    g_stock_api.osddrv_scale = (void*)OSDDRV_SCALE_ADDR;
    g_stock_api.dev_get_by_id = (void*)DEV_GET_BY_ID_ADDR;
    g_stock_api.st7789v_caset_raset = (void*)ST7789V_CASET_RASET_ADDR;
    g_stock_api.st7789v_ramwr = (void*)ST7789V_RAMWR_ADDR;

    // Libretro frontend functions
    g_stock_api.run_osd_region_write = (void*)RUN_OSD_REGION_WRITE_ADDR;
    g_stock_api.run_screen_write = (void*)RUN_SCREEN_WRITE_ADDR;
    g_stock_api.run_sound_advance = (void*)RUN_SOUND_ADVANCE_ADDR;
    g_stock_api.retro_video_refresh_cb = (void*)RETRO_VIDEO_REFRESH_CB_ADDR;
    g_stock_api.retro_audio_sample_batch_cb = (void*)RETRO_AUDIO_SAMPLE_BATCH_CB_ADDR;
    g_stock_api.retro_input_poll_cb = (void*)RETRO_INPUT_POLL_CB_ADDR;
    g_stock_api.retro_input_state_cb = (void*)RETRO_INPUT_STATE_CB_ADDR;
    g_stock_api.retro_environment_cb = (void*)RETRO_ENVIRONMENT_CB_ADDR;
    g_stock_api.run_emulator = (void*)RUN_EMULATOR_ADDR;
    g_stock_api.run_gba = (void*)RUN_GBA_ADDR;

    // Data variables
    g_stock_api.RAMSIZE = (void*)RAMSIZE_ADDR;
    g_stock_api.g_errno = (void*)G_ERRNO_ADDR;
    g_stock_api.g_snd_task_flags = (void*)G_SND_TASK_FLAGS_ADDR;
    g_stock_api.g_retro_game_info = (void*)G_RETRO_GAME_INFO_ADDR;
    g_stock_api.gfn_state_load = (void*)GFN_STATE_LOAD_ADDR;
    g_stock_api.gfn_state_save = (void*)GFN_STATE_SAVE_ADDR;
    g_stock_api.gfn_retro_get_region = (void*)GFN_RETRO_GET_REGION_ADDR;
    g_stock_api.gfn_get_system_av_info = (void*)GFN_GET_SYSTEM_AV_INFO_ADDR;
    g_stock_api.gfn_retro_load_game = (void*)GFN_RETRO_LOAD_GAME_ADDR;
    g_stock_api.gfn_retro_unload_game = (void*)GFN_RETRO_UNLOAD_GAME_ADDR;
    g_stock_api.gfn_retro_run = (void*)GFN_RETRO_RUN_ADDR;
    g_stock_api.gfn_frameskip = (void*)GFN_FRAMESKIP_ADDR;
    g_stock_api.g_run_file_size = (void*)G_RUN_FILE_SIZE_ADDR;
    g_stock_api.gp_buf_64m = (void*)GP_BUF_64M_ADDR;
    g_stock_api._ctype_ = (void*)_CTYPE__ADDR;

    // FPS Counter variables
    g_stock_api.fw_fps_counter_enable = (void*)FW_FPS_COUNTER_ENABLE_ADDR;
    g_stock_api.fw_fps_counter = (void*)FW_FPS_COUNTER_ADDR;
    g_stock_api.fw_fps_counter_format = (void*)FW_FPS_COUNTER_FORMAT_ADDR;

    // Hardware registers
    g_stock_api.PINMUXL = (void*)PINMUXL_ADDR;
    g_stock_api.PINMUXT = (void*)PINMUXT_ADDR;
    g_stock_api.GPIOLCTRL = (void*)GPIOLCTRL_ADDR;
    g_stock_api.GPIOTCTRL = (void*)GPIOTCTRL_ADDR;
    g_stock_api.lcd_font = (void*)LCD_FONT_ADDR;
}
