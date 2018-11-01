ARCH = arm
CROSS_COMPILE = arm-linux-gnueabihf-

OUTPUT=i2c_sample
TARGET_IP = 192.168.1.57

obj-m := $(OUTPUT).o

KDIR := ~/linux_kernel

PWD := $(shell pwd)

default:
	$(CROSS_COMPILE)gcc $(OUTPUT).c -o $(OUTPUT)
clean:
	@rm $(OUTPUT)
install:
	@scp $(OUTPUT)  udooer@$(TARGET_IP):~	

