#include "hal.h"
#include "debug.h"
#include <stdint.h>

// --- Internal HAL Implementation ---
typedef struct {
    int (*dly_tsk)(unsigned ms);
    // ... other function pointers will be added here
} FIRMWARE_API;

static FIRMWARE_API fw_api;

// --- Platform Detection ---
#define PLATFORM_SIGNATURE_ADDRESS      ((volatile uint32_t*)0x80c10840)
#define SF2000_RUN_EMULATOR_ADDRESS     0x803589a4
#define SF2000_DLY_TSK_ADDRESS          0x80309134
#define GB300_DLY_TSK_ADDRESS           0x802beefc

void hal_init(void) {
    if (*PLATFORM_SIGNATURE_ADDRESS == SF2000_RUN_EMULATOR_ADDRESS) {
        xlog("HAL: SF2000 platform detected.\n");
        fw_api.dly_tsk = (void*)SF2000_DLY_TSK_ADDRESS;
    } else {
        xlog("HAL: GB300 platform detected.\n");
        fw_api.dly_tsk = (void*)GB300_DLY_TSK_ADDRESS;
    }
}

// --- Transparent Wrappers ---
int dly_tsk(unsigned ms) {
    if (fw_api.dly_tsk) {
        fw_api.dly_tsk(ms);
    }
    return 0;
}

// Example of how to expand:
/*
uint32_t os_get_tick_count(void) {
    if (fw_api.os_get_tick_count) {
        return fw_api.os_get_tick_count();
    }
    return 0;
}
*/
