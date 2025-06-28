#ifndef __HAL_API_H
#define __HAL_API_H

#include <stdint.h>

typedef enum {
    PLATFORM_UNKNOWN,
    PLATFORM_SF2000,
    PLATFORM_GB300
} platform_t;

// The HAL API structure will hold pointers to all firmware functions.
// For this proof of concept, it only contains one.
typedef struct {
    int (*dly_tsk)(unsigned ms);
} HAL_API;

// A single global instance of the HAL API.
extern HAL_API hal_api;

// Initializes the HAL by detecting the platform and populating the function pointers.
platform_t hal_init(void);

#endif // __HAL_API_H