 #include<stdio.h>
 #include<sys/types.h>
 #include<unistd.h>
 #include<stdlib.h>
 int main(int argc ,char *argv[])
 {
 	if(argc !=3)
 	{
 		printf("my_kill signal pid\n");
		 return 0;
 	}
 	kill(atoi(argv[2]),atoi(argv[1]));
	 perror("kill......");
 
 } 

