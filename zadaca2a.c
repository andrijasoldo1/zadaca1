#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>

#define SHARED_MEM_SIZE (0x6400)

int shared_mem_id;
int *memory_ptr;

void handle_sigint(int sig) {
    printf("Signal primljen,gasenje..\n");
    shmdt(memory_ptr);
    shmctl(shared_mem_id, IPC_RMID, NULL);
    exit(0);
}

void update_memory(int value) {
    *memory_ptr = value;
    printf("%d\n", *memory_ptr);
    sleep(3);
    printf("%d\n", *memory_ptr);
}

int main() {
    shared_mem_id = shmget(IPC_PRIVATE, SHARED_MEM_SIZE, IPC_CREAT | 0660 );
    memory_ptr = (int*) shmat(shared_mem_id, NULL, 0);

    signal(SIGINT, handle_sigint);

    while (1) {
        if (fork() == 0) {
            update_memory(1);
            exit(0);
        }

        update_memory(2);
        wait(NULL);
    }

    return 0;
}
