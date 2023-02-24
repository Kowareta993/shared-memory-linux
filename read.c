#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "Node_std.h"
#define SHM_KEY 0x1234
#define SHM_KEY2 0x1235

typedef struct {
    int size;
    bool put;
    struct Node *node;
} shms;

void decrypt(char *text, int key)
{
    char temp;
    int i;
    for(i = 0; text[i] != '\0'; ++i){
        temp = text[i];
        text[i] = temp - key;
    }
  
}

int main(int argc, char *argv[]) {  
    int shmid = shmget(SHM_KEY, sizeof(shms), 0666|IPC_CREAT);
    if(shmid == -1) {
        perror("shared mem error");
        exit(1);
    }
    shms *shm = (shms *) shmat(shmid, (void *) 0, 0);
    if(!shm->put) {
        shm->size = atoi(argv[1]);
        shm->put = true;
    }
    int shmid2 = shmget(SHM_KEY2, sizeof(struct Node) * shm->size, 0666|IPC_CREAT);
    if(shmid2 == -1) {
        perror("shared mem error");
        exit(1);
    }
    shm->node = (struct Node *) shmat(shmid2, (void *) 0, 0);
    int i = 0;
    char buffer[200];
    
    while (i < shm->size) {
        strcpy(buffer, shm->node[i].value);
        decrypt(buffer, shm->node[i].key);
        printf("%s", buffer);
        i++;
    }
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID, NULL);
    return 0;
}

