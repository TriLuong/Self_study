#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>

#include <string.h>

#include <unistd.h>

#define My_Print 'P'
#define Print_Hi _IOWR(My_Print, 10, unsigned long)
#define Print_Bye _IOWR(My_Print, 11, unsigned long)

int main(int argc, char **argv)
{
	int fd;
	if ((fd = open("/dev/my_device_1_device", O_RDWR)) < 0){
		printf("ERROR when opening /dev/my_device_1_device\n");
		return fd;
	}

	if(argc == 2){
		if (!strcmp(argv[1],"Hi")){
			ioctl(fd,Print_Hi,argv[1]);
			printf("Dich: Xin chao\n");
		}
		else if (!strcmp(argv[1],"Bye")){
			ioctl(fd,Print_Bye,argv[1]);
			printf("Dich: Tam biet\n");
		} 
		else{
			printf("Tu nay khong co trong tu dien\n");
		}
	}
	else{
		printf("Nhap sai roi\n");
	}

}
