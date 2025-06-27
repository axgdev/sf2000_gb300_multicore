#ifndef __SF2000_VIDEO_H
#define __SF2000_VIDEO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "file/config_file.h"
#include "hal.h"

#define HLD_DEV_TYPE_DIS	0x10f0000

enum tvsystem {
	PAL	= 0, // C implies this but ALi have it specified anyway
	NTSC,
	RGB_LCD	= 0x16 // LINE_800x480_60 hacked for RGB output by HiChip
};

struct vp_init_info; // all of it's rather large thus better patched in-place

// is_lcd is named switch_flag in debug printf (it's redunant btw)

/* enum DIS_RGB_CLOCK in libviddrv.a. Do note them renaming from
https://git.maschath.de/ignatz/hcrtos/-/blob/main/board/hc15xx/common/dts/sf2000_min.dts#L592
(device tree is likely an older effort, pasting the driver's source verbatim) */
enum VPO_RGB_CLOCK {
	VPO_RGB_CLOCK_6_6M	= 8,
	VPO_RGB_CLOCK_9M	= 9
};

#define VPO_IO_GET_OUT_MODE	3

#define HLD_DEV_TYPE_OSD	0x1030000

struct osdrect {
	uint16_t u_left;
	uint16_t u_top;
	uint16_t u_width;
	uint16_t u_height;
};

enum osdcolor_mode {
	OSD_HD_RGB565	= 5,
	OSD_HD_ARGB8888	= 10 // currently unused (needs a run_emulator_menu hook)
};

struct osdpara {
	enum osdcolor_mode e_mode;
	uint8_t u_galpha_enable;
	uint8_t u_galpha;
	uint8_t u_pallette_sel; // sic
	uint8_t u_rotate; // hangs the driver; needs serious research to fix
	uint8_t u_flip_v;
	uint8_t u_flip_h;
};

struct osd_vscr {
	struct osdrect v_r;
	const void *lpb_scr;
	uint8_t	b_block_id;
	BOOL update_pending;
	uint8_t b_color_mode; // implies enum osdcolor_mode. ALi's fav bad practice
	uint8_t b_draw_mode;
};

#define OSD_SET_SCALE_MODE	0x0B

#define OSD_SCALE_DUPLICATE	0
#define OSD_SCALE_FILTER	1

#define OSD_SCALE_WITH_PARAM	0x0C

struct osd_scale_param {
	uint16_t tv_sys; // implies enum tvsystem (NOT enum TV_SYS_TYPE)
	uint16_t h_div;
	uint16_t v_div;
	uint16_t h_mul;
	uint16_t v_mul;
};

void video_options(config_file_t *config);
void video_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif

#define HLD_DEV_TYPE_DIS	0x10f0000

enum tvsystem {
	PAL	= 0, // C implies this but ALi have it specified anyway
	NTSC,
	RGB_LCD	= 0x16 // LINE_800x480_60 hacked for RGB output by HiChip
};

struct vp_init_info; // all of it's rather large thus better patched in-place

// is_lcd is named switch_flag in debug printf (it's redunant btw)

/* enum DIS_RGB_CLOCK in libviddrv.a. Do note them renaming from
https://git.maschath.de/ignatz/hcrtos/-/blob/main/board/hc15xx/common/dts/sf2000_min.dts#L592
(device tree is likely an older effort, pasting the driver's source verbatim) */
enum VPO_RGB_CLOCK {
	VPO_RGB_CLOCK_6_6M	= 8,
	VPO_RGB_CLOCK_9M	= 9
};

#define VPO_IO_GET_OUT_MODE	3

#define HLD_DEV_TYPE_OSD	0x1030000

struct osdrect {
	uint16_t u_left;
	uint16_t u_top;
	uint16_t u_width;
	uint16_t u_height;
};

enum osdcolor_mode {
	OSD_HD_RGB565	= 5,
	OSD_HD_ARGB8888	= 10 // currently unused (needs a run_emulator_menu hook)
};

struct osdpara {
	enum osdcolor_mode e_mode;
	uint8_t u_galpha_enable;
	uint8_t u_galpha;
	uint8_t u_pallette_sel; // sic
	uint8_t u_rotate; // hangs the driver; needs serious research to fix
	uint8_t u_flip_v;
	uint8_t u_flip_h;
};

struct osd_vscr {
	struct osdrect v_r;
	const void *lpb_scr;
	uint8_t	b_block_id;
	BOOL update_pending;
	uint8_t b_color_mode; // implies enum osdcolor_mode. ALi's fav bad practice
	uint8_t b_draw_mode;
};

#define OSD_SET_SCALE_MODE	0x0B

#define OSD_SCALE_DUPLICATE	0
#define OSD_SCALE_FILTER	1

#define OSD_SCALE_WITH_PARAM	0x0C

struct osd_scale_param {
	uint16_t tv_sys; // implies enum tvsystem (NOT enum TV_SYS_TYPE)
	uint16_t h_div;
	uint16_t v_div;
	uint16_t h_mul;
	uint16_t v_mul;
};

void video_options(config_file_t *config);
void video_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif
#include "hal.h"

#define HLD_DEV_TYPE_DIS	0x10f0000

enum tvsystem {
	PAL	= 0, // C implies this but ALi have it specified anyway
	NTSC,
	RGB_LCD	= 0x16 // LINE_800x480_60 hacked for RGB output by HiChip
};

struct vp_init_info; // all of it's rather large thus better patched in-place

// is_lcd is named switch_flag in debug printf (it's redunant btw)

/* enum DIS_RGB_CLOCK in libviddrv.a. Do note them renaming from
https://git.maschath.de/ignatz/hcrtos/-/blob/main/board/hc15xx/common/dts/sf2000_min.dts#L592
(device tree is likely an older effort, pasting the driver's source verbatim) */
enum VPO_RGB_CLOCK {
	VPO_RGB_CLOCK_6_6M	= 8,
	VPO_RGB_CLOCK_9M	= 9
};

#define VPO_IO_GET_OUT_MODE	3

#define HLD_DEV_TYPE_OSD	0x1030000

struct osdrect {
	uint16_t u_left;
	uint16_t u_top;
	uint16_t u_width;
	uint16_t u_height;
};

enum osdcolor_mode {
	OSD_HD_RGB565	= 5,
	OSD_HD_ARGB8888	= 10 // currently unused (needs a run_emulator_menu hook)
};

struct osdpara {
	enum osdcolor_mode e_mode;
	uint8_t u_galpha_enable;
	uint8_t u_galpha;
	uint8_t u_pallette_sel; // sic
	uint8_t u_rotate; // hangs the driver; needs serious research to fix
	uint8_t u_flip_v;
	uint8_t u_flip_h;
};

struct osd_vscr {
	struct osdrect v_r;
	const void *lpb_scr;
	uint8_t	b_block_id;
	BOOL update_pending;
	uint8_t b_color_mode; // implies enum osdcolor_mode. ALi's fav bad practice
	uint8_t b_draw_mode;
};

#define OSD_SET_SCALE_MODE	0x0B

#define OSD_SCALE_DUPLICATE	0
#define OSD_SCALE_FILTER	1

#define OSD_SCALE_WITH_PARAM	0x0C

struct osd_scale_param {
	uint16_t tv_sys; // implies enum tvsystem (NOT enum TV_SYS_TYPE)
	uint16_t h_div;
	uint16_t v_div;
	uint16_t h_mul;
	uint16_t v_mul;
};

void video_options(config_file_t *config);
void video_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif
