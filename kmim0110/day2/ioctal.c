#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <linux/input.h>

int main(int argc, char *argv[])
{
	int fd;
	char buf[4096];
	char name[256] = "Unknown";
	fd=open(argv[1],O_RDONLY);
	if(fd<0)
	{
		perror("Open Fails");
		return -1;
	}
        ioctl(fd, EVIOCGNAME(sizeof(name)), name);
        printf("Input device name: \"%s\"\n", name);

	return 0;
}

