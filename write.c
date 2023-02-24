#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<fcntl.h>
#include "Node_std.h"
#define SHM_KEY 0x1234
#define SHM_KEY2 0x1235

typedef struct {
    int size;
    bool put;
    struct Node *node;
} shms;


void encrypt(char *text, int key) {
    char temp;
    int i;
    for(i = 0; text[i] != '\0'; ++i){
        temp = text[i];
        text[i] = temp + key;
    }
}

int get_line(char *buffer, char *line,int start, int size) {
    int i = 0;
    while(i + start < size) {
        line[i] = buffer[i + start];
        if (line[i] == '\n') {
            line[i+1] = '\0';
            return start + i + 1;
        }
        i++;
    }
    return size;
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
    char buffer[4096];
    int bufsize = 4096;
    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid == 0){
        sprintf(buffer, "%d", shm->size);
        close(fd[0]);
        dup2(fd[1], 1);
        char *argv_list[] = {"/bin/sh", "./script.sh", buffer,  argv[2], NULL};
        execv("/bin/sh", argv_list);
        close(fd[1]);
        exit(0);
    }
    else if (pid < 0) {
        exit(1);
    }
    else {
        close(fd[1]);
        dup2(fd[0], 0);
        int c = 0;
        int nbytes;
        char line[4096];
        int s = 0;
        int i = 0;
        int key;
        while (i < shm->size) {
            nbytes = read(STDIN_FILENO, buffer, 4096);
            s = get_line(buffer, line, s, nbytes);
            key = rand() % 128;
            encrypt(line, key);
            strcpy(shm->node[i].value, line);
            shm->node[i].key = key;
            i++;
            while(s != nbytes) {
                s = get_line(buffer, line, s, nbytes);
                key = rand() % 128;
                encrypt(line, key);
                strcpy(shm->node[i].value, line);
                shm->node[i].key = key;
                i++;
            }

        }
    }
    
    return 0;
}

