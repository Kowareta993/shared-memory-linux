#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "Node_std.h"
#define LIST_SIZE 50
#define SHM_KEY 0x1234
int main(int argc, char *argv[]) {
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
  
    // shmget returns an identifier in shmid
    // int shmid = shmget(key, sizeof(struct Node) * LIST_SIZE, 0666|IPC_CREAT);
    int shmid = shmget(SHM_KEY, sizeof(int), 0666|IPC_CREAT);
    
    // shmat to attach to shared memory
    int *size = (int*) shmat(shmid, (void*) 0, 0);
    *size = -1;
    int pid = fork();
    if (pid == 0) {
        //read
        if(*size == -1) {
            *size = atoi(argv[1]);
        }
        exit(0);
    }
    else if (pid < 0) {
        exit(1);
    }
    else {
        //write
        if(*size == -1) {
            *size = atoi(argv[1]);
        }
        exit(0);
    }
    return 0;
}