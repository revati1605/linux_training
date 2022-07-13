#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("./a.out filename");
		return 0;
	}
	int in;
	in=open(argv[1],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	close(in);
	return 0;
}
