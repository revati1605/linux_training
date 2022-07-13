#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
void my_system(char *);

int main(int argc,char *argv[])
{
	my_system(argv[1]);
	return 0;
}
void my_system(char * p)
{
	int status,ret;
	if(fork() == 0)
	{
		ret=execl("/bin/sh", "sh", "-c", p, (char *) NULL);
		if(ret == -1)
		{
			perror("execl fail");
		}
		exit(1);
	}
	else
	{
		wait(&status);
	}
}
		

