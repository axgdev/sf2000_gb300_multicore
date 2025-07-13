#ifndef HAL_API_H
#define HAL_API_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdio.h>
#include "stockfw.h"

void patch_hal_api(int platform);
void restore_stock_gp(int platform);

// External declarations for data symbols that will be patched
// Note: Most of these are already declared in stockfw.h, we just need the ones that aren't
extern int *g_errno;

// Hardware register pointers
extern volatile uint32_t *PINMUXL;
extern volatile uint32_t *PINMUXT;
extern volatile uint32_t *GPIOLCTRL;
extern volatile uint32_t *GPIOTCTRL;

int *fw_fps_counter_enable;
int *fw_fps_counter;
char *fw_fps_counter_format;

#endif
