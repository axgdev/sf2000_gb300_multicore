#include "hal_api.h"
#include "debug.h"

// The global instance of our HAL API struct (defined as static to this file)
static HAL_API g_hal_struct;
// The global pointer that all other files will use for fast access.
HAL_API *g_hal = &g_hal_struct;

// Use a known function pointer's address and value to differentiate the platforms
// This address points to the 'gfn_retro_run' pointer in the SF2000's firmware.
#define PLATFORM_SIGNATURE_ADDRESS      ((volatile uint32_t*)0x80c10840)
// This is the value that 'gfn_retro_run' points to on the SF2000.
#define SF2000_RUN_EMULATOR_ADDRESS     0x803589a4

void hal_init(void) {
    // Runtime platform detection: This 'if' runs only ONCE at startup.
    if (*PLATFORM_SIGNATURE_ADDRESS == SF2000_RUN_EMULATOR_ADDRESS) {
        // --- Platform is SF2000 ---
        xlog("HAL: SF2000 platform detected.\n");
        g_hal_struct.dly_tsk = (void*)0x80309134;
    } else {
        // --- Platform is GB300 ---
        xlog("HAL: GB300 platform detected.\n");
        g_hal_struct.dly_tsk = (void*)0x802beefc;
    }
}
