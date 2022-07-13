#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	if(fork() == 0)
	{
		printf("child process ,pid=%d,ppid=%d\n",getpid(),getppid());
		sleep(10);
	}
	else
	{
		printf("parent process,pid=%d ppid=%d\n",getpid(),getppid());
		while(1);
	}
}
