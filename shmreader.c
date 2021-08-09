#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    char     name[15];
    uint8_t  count;
} write_det;

int main()
{
    int shm_id = -1;
    key_t shmkey;

    if (-1 == (shmkey = ftok("details", 33))) {
        printf("Reader: Shm key gen failed\n");
        return 0;
    }

    if (-1 == (shm_id = shmget(shmkey, sizeof(write_det), IPC_CREAT))) {
        printf("Reader: shm creation failed\n");
        return 0;
    }

    write_det *shmem_cons = (write_det *) shmat(shm_id, 0, 0);
    if (shmem_cons == NULL) {
        printf("Reader: shm attach failed\n");
        return 0;
    }

    printf("Reader:\n");
    printf("Name: %s\n", shmem_cons->name);
    printf("Count:%d\n", shmem_cons->count);

    shmdt(shmem_cons);
    /* delete shm block */
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}

