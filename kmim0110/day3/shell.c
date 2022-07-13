#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
int main()
{
pid_t pid;
int ret,status;
char *argv[]={"ls","-l"};
if (fork() == 0)
{
	printf("child process\n");
	ret = execve("/bin/ls",argv,NULL);
	if(ret == -1)
	{
		perror("execve fail....");
		exit(0);
	}

}
else
{
	printf("parent process\n");
	wait(&status);
}
}
