#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

sem_t empty,full;
int shmid;
char *msg;
pid_t pid;

int main()
{
	shmid = shmget(10, 1024, 0666 | IPC_CREAT);
        if (shmid == -1)
        {	
            	perror("Shared memory error!");
            	exit(0);
        }

	sem_init(&empty, 0, 26);
	sem_init(&full, 0, 0);
	
	pid=fork();

	if(pid==0){
	     
		printf("invoke the child process:reading the data from the buffer\n");
		int out=0,y=26;
    		char out1[26];
    		
		msg=shmat(shmid,0,0);
 
    		while(y>0){
    			sem_wait(&full);
    			out1[out]=msg[out];
    			out=(out+1)%26;
    			if(out==0){
    				printf("\t c: %s\n",out1);	
    				sleep(1);
    			}
    			y--;
    			sem_post(&empty);
    		}
    		shmdt(msg);

        	
	}
	else{

		printf("parent process is running producer: writing the data into the buffer\n");
		int in = 0,x=0;
    		char ch = 'A';
    		msg=shmat(shmid,0,0);    	
    		while(x<26){
    			sem_wait(&empty);

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
			sem_post(&full);
		
		}
		shmdt(msg);

	}
	return 0;
}
