#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void producer(int sig);
void consumer(int sig);
int shmid;
char *msg;
pid_t pid;
//char buffer[26];
int main(){

	shmid = shmget(10, 1024, 0666|IPC_CREAT);
        if (shmid == -1)
        {	
            	perror("Shared memory error!");
            	exit(0);
        }

	pid=fork();
	if(pid==0){
	        (void) signal(SIGUSR1,consumer);
		printf("invoke the child process:reading the data from the buffer");

        	kill(getppid(), SIGUSR2);

        	while(1){
        		pause();
        	}
        	
	}
	else{
		(void)signal(SIGUSR2, producer);
		printf("parent process is running producer: writing the data into the buffer");

		while(1){
			pause();
		}
	}
	return 0;
}
void producer(int sig){
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
		
	}
	
	shmdt(msg);
	kill(pid,SIGUSR1);
}
void consumer(int sig){
	int out=0,y=26;
    	char out1[26];
    	
    	msg=shmat(shmid,0,0);
    	while(y>0){

    		out1[out]=msg[out];
    		out=(out+1)%26;
    		if(out==0){
    			printf("\t c: %s\n",out1);	
    			sleep(1);
    		}
    		y--;
    	}
    	shmdt(msg);
    	kill(getppid(),SIGUSR2);
}
