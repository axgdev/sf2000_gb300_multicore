#ifndef __HAL_API_H
#define __HAL_API_H

// The HAL API structure will hold pointers to all firmware functions.
// For this proof of concept, it only contains one.
typedef struct {
    int (*dly_tsk)(unsigned ms);
} HAL_API;

// // A single global instance of the HAL API.
// extern HAL_API hal_api;

// // Initializes the HAL by detecting the platform and populating the function pointers.
// void hal_init(void);

#include "debug.h"
#include <stdint.h>

// The global instance of the HAL API structure.
HAL_API hal_api;

// Use a known instruction address and value to differentiate the platforms
// I'm using an unannotated function as it is less likely to be used by the core
#define PLATFORM_SIGNATURE_ADDRESS      ((volatile uint32_t*)0x80004da4)
#define SF2000_JAL_FUN_80004570_INSTRUCTION  0x0c00115c

// Addresses for dly_tsk from the original linker scripts
#define SF2000_DLY_TSK_ADDRESS  0x80309134
#define GB300_DLY_TSK_ADDRESS   0x802beefc

static inline void hal_init(void) {
    // Runtime platform detection:
    // Check the value at the known address for SF2000's 'gfn_retro_run' pointer.
    // If it contains the address of SF2000's 'run_emulator', we are on an SF2000.
    if (*PLATFORM_SIGNATURE_ADDRESS == SF2000_JAL_FUN_80004570_INSTRUCTION) {
        xlog("HAL:SF2000\n");
        hal_api.dly_tsk = (void*)SF2000_DLY_TSK_ADDRESS;
        xlog("set\n");
    } else {
        xlog("HAL:GB300\n");
        hal_api.dly_tsk = (void*)GB300_DLY_TSK_ADDRESS;
    }
}

#endif // __HAL_API_H