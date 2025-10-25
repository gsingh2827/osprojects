Producer–Consumer Problem (C / Linux)

Program Description

This project implements the Producer–Consumer Problem using two separate processes that communicate through shared memory and synchronize using POSIX semaphores.

The producer process generates items (A–J) and writes them into a shared buffer.

The consumer process reads items from the same buffer and displays them.

The shared buffer (table) can hold two items at a time.

Semaphores ensure proper synchronization:

Producer waits when buffer is full.

Consumer waits when buffer is empty.

Both use a mutex semaphore for mutual exclusion.

Features implemented:

Process-level communication (not threads)

Shared memory for data exchange

Semaphores for synchronization

Mutual exclusion to avoid race conditions

Usage Instructions (5 points)

Follow these steps to compile and run the programs on Linux (tested on Kent State server WASP, Ubuntu-based system using VS Code remote connection).

Environment Setup:
sudo apt update
sudo apt install build-essential

Step 1 – Compile Both Programs
Use the following commands in the terminal to compile both source files:
gcc producer.c -o producer -pthread -lrt -Wall
gcc consumer.c -o consumer -pthread -lrt -Wall

Step 2 – Run the Programs (Simultaneous Execution in One Terminal)
Both producer and consumer should run at the same time.
Use the following commands to start them in the background:

./producer & ./consumer &

This runs both processes concurrently in a single terminal.
The producer will generate items and place them into shared memory, while the consumer retrieves and displays them using semaphores for synchronization.



Explanation of Key Components :

Shared Memory:
Shared memory allows two separate processes to access the same region of memory.

Created with:
int shm_fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, 0666);
ftruncate(shm_fd, sizeof(shared_data));
shared_data *data = mmap(0, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

shm_open() creates or opens a shared memory object.
ftruncate() sets its size.
mmap() maps it into both processes’ address space.

Semaphores:
Semaphores control process access to the shared buffer.

Semaphore Purpose Initial Value
/sem_empty Counts empty slots in buffer 2
/sem_full Counts filled slots 0
/sem_mutex Controls mutual exclusion 1

Typical usage:
sem_wait(empty); // wait for space
sem_wait(mutex); // enter critical section
// write item to buffer
sem_post(mutex); // leave critical section
sem_post(full); // signal item available

Mutual Exclusion:
sem_wait(mutex) and sem_post(mutex) protect the critical section to prevent both producer and consumer from modifying shared memory simultaneously.

RESULT SCREENSHOT :
[results.png.png]


