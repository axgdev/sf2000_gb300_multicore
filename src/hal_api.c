#include "hal_api.h"
#include "debug.h"

// The global instance of the HAL API structure.
HAL_API hal_api;

// Use a known instruction address and value to differentiate the platforms
// I'm using an unannotated function as it is less likely to be used by the core
#define PLATFORM_SIGNATURE_ADDRESS      ((volatile uint32_t*)0x80004da4)
#define SF2000_JAL_FUN_80004570_INSTRUCTION  0x0c00115c

// Addresses for dly_tsk from the original linker scripts
#define SF2000_DLY_TSK_ADDRESS  0x80309134
#define GB300_DLY_TSK_ADDRESS   0x802beefc

// This is the stock firmware's global pointer value.
// We get this from the stock firmware's startup code at 0x80001274
#define STOCK_GP_VALUE 0x80c114f4

// --- The Trampoline Macro ---
// This macro hides the complex assembly needed to safely call a stock firmware function.
// It saves our loader's $gp, sets the stock firmware's $gp, calls the function,
// and then restores our loader's $gp.
#define CALL_FIRMWARE(func_ptr, ...) \
    ({ \
        int (*_func)(unsigned int) = (int (*)(unsigned int))func_ptr; \
        register unsigned long _stock_gp asm("gp") = STOCK_GP_VALUE; \
        __asm__ __volatile__("" : "+r"(_stock_gp)); \
        _func(__VA_ARGS__); \
    })


platform_t hal_init(void) {
    platform_t detected_platform = PLATFORM_UNKNOWN;
    // Runtime platform detection:
    // Check the value at the known address for SF2000's 'gfn_retro_run' pointer.
    // If it contains the address of SF2000's 'run_emulator', we are on an SF2000.
    if (*PLATFORM_SIGNATURE_ADDRESS == SF2000_JAL_FUN_80004570_INSTRUCTION) {
        detected_platform = PLATFORM_SF2000;
        hal_api.dly_tsk = (void*)SF2000_DLY_TSK_ADDRESS;
    } else {
        // We assume any other signature is a GB300 for now.
        detected_platform = PLATFORM_GB300;
        hal_api.dly_tsk = (void*)GB300_DLY_TSK_ADDRESS;
    }

    return detected_platform;
}

// Transparent Trampoline:
// This function has the *exact same name and signature* as the original function.
// The linker will direct all calls for 'dly_tsk' to this implementation.
// This implementation then safely calls the real firmware function via the trampoline.
int dly_tsk(unsigned ms) {
    // The return value from the real dly_tsk is often inconsistent or ignored.
    // We can call it and return a consistent value.
    CALL_FIRMWARE(hal_api.dly_tsk, ms);
    return 0;
}