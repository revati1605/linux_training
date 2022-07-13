#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		printf("./a.out file1 file2\n");
		return 0;
	}
	int in,out,nread;
	char byte;
	in=open(argv[1], O_RDONLY);
	if(in < 0)
	{
		perror("open file");
		printf("errno:%d\n",errno);
		exit(0);
	}
	out=open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	if(out < 0)
	{
		perror("open file");
		printf("errno:%d\n",errno);
		exit(0);
	}
	while((nread=read(in,&byte,1))>0)
	write(out,&byte,nread);
	close(in);
	close(out);
}
