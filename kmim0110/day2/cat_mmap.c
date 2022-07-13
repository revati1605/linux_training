#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc,char *argv[])
{
	int i,ret,fd;
	struct stat temp;
	char *buffer,*temp1;
	
	fd = open(argv[1],O_RDONLY);
	ret = fstat(fd,&temp);
	if (ret < 0)
	perror("stat error");
//	printf("size of the %s file:%ld\n",argv[1],temp.st_size);
	buffer = (char *) mmap(0,temp.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	temp1=buffer;
	for(i=0;i<=temp.st_size;i++)
	 {
		printf("%c",*buffer);
		buffer++;
	}	
	munmap(temp1,temp.st_size);	
	return 0;
}
