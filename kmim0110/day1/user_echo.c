#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
#include<stdlib.h>
int main(int argc ,char *argv[])
{
	if(argc < 2)
	{
		printf("./a.out argument\n");
		return 0;
	}
	int ctr,count=0;
	for(ctr=0;argv[1][ctr];ctr++)
	{
		count++;
	}
	for(ctr=1;ctr<argc;ctr++)
	write(1,argv[ctr],count);

} 
