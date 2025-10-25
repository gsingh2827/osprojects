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

    sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, BUFFER_SIZE);
    sem_t *full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(shared_data));
    data = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    data->count = 0;

    for (int i = 0; i < 10; i++) {
        sem_wait(empty);
        sem_wait(mutex);

        data->buffer[data->count++] = 'A' + i;
        printf("Produced: %c\n", 'A' + i);

        sem_post(mutex);
        sem_post(full);

        sleep(1);
    }

    munmap(data, sizeof(shared_data));
    close(shm_fd);
    return 0;
}
