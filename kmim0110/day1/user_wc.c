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
	int in,count=1,size=0,l=0,ret,nread;
	char byte;	
	in=open(argv[1],O_RDONLY);
	if(in < 0 )
	{
		perror("open file:");
		printf("errno:%d\n",errno);
	}
	while((nread=read(in,&byte,1))>0)
	{
		size++;
		if(byte == '\n')
		{
			l++;
		}
		if(byte == ' ')
		{
			count++;
		}
	
	}
//	ret=lseek(in,0,SEEK_SET);
//	printf("ret:%d count:%d l:%d\n",ret,count,l);
//	while((ret=read(in,arr,sizeof(arr)))!=-1)
//		count++;
	printf("%d %d %d %s\n",l,count,size,argv[1]);

}
	
