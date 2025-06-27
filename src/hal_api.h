#ifndef __HAL_API_H
#define __HAL_API_H

#include <stdint.h>

// Minimal HAL API for the proof of concept
typedef struct {
    // We will abstract only one function to start
    int (*dly_tsk)(unsigned ms);

} HAL_API;

// Declare an external pointer to the HAL structure for fast access.
extern HAL_API *g_hal;

// Define a convenience macro for clean and efficient calling.
#define HAL(func) (g_hal->func)

// The function to initialize the HAL
void hal_init(void);

#endif // __HAL_API_H
