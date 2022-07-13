#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("./a.out filename \n");
		return 0;
	}
	int in,nread;
	char buf;
	in=open(argv[1],O_RDONLY);
	if(in < 0)
	{
		perror("open fails");
		printf("errno:%d\n",errno);
		exit(0);
	}
	while((nread=read(in,&buf,1))>0)
	{
		write(1,&buf,nread);
	}
	close(in);
	return 0;
}

	
