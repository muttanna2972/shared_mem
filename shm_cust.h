#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    char     name[15];
    uint8_t  count;
} write_det;
