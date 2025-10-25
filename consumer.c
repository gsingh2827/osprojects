#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

#define SHM_NAME "/my_shared_memory"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"
#define SEM_MUTEX "/sem_mutex"
#define BUFFER_SIZE 10

typedef struct {
    char buffer[BUFFER_SIZE];
    int count;
} shared_data;

int main() {
    int shm_fd;
    shared_data *data;

    sem_t *empty = sem_open(SEM_EMPTY, 0);
    sem_t *full = sem_open(SEM_FULL, 0);
    sem_t *mutex = sem_open(SEM_MUTEX, 0);

    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    data = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    for (int i = 0; i < 10; i++) {
        sem_wait(full);
        sem_wait(mutex);

        char item = data->buffer[--data->count];
        printf("Consumed: %c\n", item);

        sem_post(mutex);
        sem_post(empty);

        sleep(1);
    }

    munmap(data, sizeof(shared_data));
    close(shm_fd);
    shm_unlink(SHM_NAME);

    sem_unlink(SEM_EMPTY);
    sem_unlink(SEM_FULL);
    sem_unlink(SEM_MUTEX);

    return 0;
}
