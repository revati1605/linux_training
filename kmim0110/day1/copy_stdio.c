#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	if(argc != 3 )
	{
		printf("./a.out file1 file2 \n");
		return 0;
	}
    	int c;
    	FILE *in, *out;

    	in = fopen(argv[1],"r");
    	out = fopen(argv[2],"w");

    	while((c = fgetc(in)) != EOF)
        	fputc(c,out);

 
}
