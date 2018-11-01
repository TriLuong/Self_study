#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>


int main(int argc, char **argv)
{
	int fd;
	if ((fd = open("/dev/i2c-0", O_RDWR)) < 0){
		printf("ERROR when opening /i2c-0\n");
		return fd;
	}

	printf("[INFO] Can open i2c-0\n");

}
