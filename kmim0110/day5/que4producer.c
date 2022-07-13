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
    	int in = 0,x=0;
    	char ch = 'A';
    	msg=shmat(shmid,0,0);    	
    	
    	while(x<26){

    		msg[in]=ch;
    		in = (in + 1) % 26;
    		ch++;
        	if (in == 0)
		{
			ch = 'A';
			printf("p:%s\n",msg);
			sleep(1);
		}
		x++;
		sem_post(full);
	}
	
	shmdt(msg);
}

