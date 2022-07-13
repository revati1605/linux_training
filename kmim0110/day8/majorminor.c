#include<stdio.h>
int main()
{
	unsigned int a=0xaabbccdd;
	printf("Major:%x\n",a>>20);
	printf("Minor:%x\n",a&0x000fffff);

}
