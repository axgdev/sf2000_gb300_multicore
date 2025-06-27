#ifndef __STOCKFW_H
#define __STOCKFW_H

#include <stdbool.h>
#include <stdint.h>

#define FS_O_RDONLY     0x0000
#define FS_O_WRONLY     0x0001
#define FS_O_RDWR       0x0002
#define FS_O_APPEND     0x0008
#define FS_O_CREAT      0x0100
#define FS_O_TRUNC      0x0200

typedef int BOOL;
typedef uintptr_t HANDLE;

#endif
