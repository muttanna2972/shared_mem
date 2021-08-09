#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    char     name[15];
    uint8_t  count;
} write_det;

write_det g_prod;

int main()
{
    int shm_id = -1;
    key_t shmkey;

    memset(&g_prod, 0, sizeof (write_det));
    strcpy(g_prod.name, "shared mem");
    g_prod.count = 100; /*Some random number */

    if (-1 == (shmkey = ftok("details", 33))) {
        printf("Write: Shm key gen failed\n");
        return 0;
    }

    if (-1 == (shm_id = shmget(shmkey, sizeof(write_det), IPC_CREAT))) {
        printf("Write: shm creation failed\n");
        return 0;
    }

    write_det *shmem_prod = (write_det *) shmat(shm_id, 0, 0);
    memcpy(shmem_prod, &g_prod, sizeof (write_det));
    printf("Write: Date written to SHM\n");
    /* should it be detached before read? */

    return 0;
}
