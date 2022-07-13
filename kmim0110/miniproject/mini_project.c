
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

char *fbname;
int FrameBufferFD,fd1,bytes;
struct fb_fix_screeninfo fix_info;
struct fb_var_screeninfo var_info;
void *framebuffer;
unsigned long int screensize,BMPscreensize;
unsigned char buff[80];
char cmp[]="BM";
int x_axis,y_axis;
unsigned int *fb_ptr;
int line_length;
unsigned int *res;
int main()
{
	int size;
	
	int x, y;
	
	fbname = "/dev/fb0";
	FrameBufferFD = open(fbname, O_RDWR);
	if (FrameBufferFD < 0) {
		printf("Unable to open %s.\n", fbname);
	return 1;
	}


if (ioctl(FrameBufferFD, FBIOGET_FSCREENINFO, &fix_info) < 0) {
	printf("get fixed screen info failed: %s\n",
	strerror(errno));
	close(FrameBufferFD);
	return 1;
}

if (ioctl(FrameBufferFD, FBIOGET_VSCREENINFO, &var_info) < 0) {
	printf("Unable to retrieve variable screen info: %s\n",
	strerror(errno));
	close(FrameBufferFD);
	return 1;
}

printf("Screen resolution: (%dx%d)\n", var_info.xres,var_info.yres);
printf("Line width in bytes %d\n", fix_info.line_length);
printf("bits per pixel : %d\n", var_info.bits_per_pixel);
screensize=var_info.xres*var_info.yres*(var_info.bits_per_pixel/8);
printf("The screensize of the frame is %lu\n",screensize);
fd1=open("KM-logo_1920_1080_32bpp.bmp",O_RDONLY);
/*bytes=read(fd1,buff,2);
printf("%s\n",buff);
if (strcmp(cmp,buff))
{
	perror("Fails to open :");
	exit(0);
}*/
read(fd1,buff,54);


x_axis=(buff[18]|(buff[19]<<8)|(buff[20]<<16)|(buff[21]<<24));
y_axis=(buff[22]|(buff[23]<<8)|(buff[24]<<16)|(buff[25]<<24));


printf("x_axis : %d\n",x_axis);
printf("y_axis : %d\n",y_axis);
printf("Number of bites per pixel %d\n",buff[28]);
BMPscreensize=x_axis*y_axis*(buff[28]/8);
if (BMPscreensize > screensize)
{
	printf("The BMP resolution is more than frame buffer resolution\n");
}
printf("The screensize of the BMP frame is %lu\n",BMPscreensize);
size=fix_info.line_length * var_info.yres;
fb_ptr = (unsigned int *) mmap (0, size, PROT_READ|PROT_WRITE, MAP_SHARED, FrameBufferFD , 0);
//lseek(fd1,54,SEEK_SET);
line_length=fix_info.line_length/4;
for (int i=y_axis-1;i>=0;i--)
{
	for (int j=0;j<x_axis;j++)
	{
		read(fd1,&res,4);
		fb_ptr[i*line_length+j]=res;
	}
}
return 0;
}
