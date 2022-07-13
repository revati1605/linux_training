#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<stdio.h>

int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		printf("./a.out file1 file2\n");
		return 0;
	}
   	 char byte; 
    	int in, out; 
    	int nread;

    	in = open(argv[1], O_RDONLY); 
   	out = open(argv[2], O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    	while((nread = read(in,&byte,1)) > 0)
        	write(out,&byte,nread);
}

