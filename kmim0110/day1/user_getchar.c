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
		printf("./a.out filename\n");
		return 0;
	}
	int fd;
	char byte;
	fd=open(argv[1],O_RDONLY);
	if(fd < 0)
	{
		perror("open file");
	}
	read(fd,&byte,1);
	printf("%c",byte);
}
	
