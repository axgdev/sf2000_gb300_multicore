#ifndef __HAL_H
#define __HAL_H

// This is the only function the rest of the loader needs to know about.
// It detects the platform and patches the necessary function pointers.
void hal_init(void);

// We declare our transparent wrappers here so other modules can see them.
int dly_tsk(unsigned ms);

#endif // __HAL_H
