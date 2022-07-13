#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <string.h>
int shmid;
char *msg;
sem_t *empty, *full;
int main(){
	int ret;
    	shmid = shmget(10, 1024, 0666 | IPC_CREAT);
    	if (shmid == -1)
    	{
        	perror("Shared memory error!");
        	exit(0);
    	}
    	full = sem_open("csem", O_CREAT, 0664, 0);
    	empty = sem_open("psem", O_CREAT, 0664, 26);
    	int out=0,y=26;
    	char out1[26];
    	
    	msg=shmat(shmid,0,0);
    	while(y>0){
    		sem_wait(full);
		sem_wait(empty);
    		out1[out]=msg[out];
    		out=(out+1)%26;
    		if(out==0){
    			printf("\t c: %s\n",out1);	
    			sleep(1);
    		}
    		y--;
    		sem_post(empty);
    		
    	}
    	shmdt(msg);
}
