ARCH = arm
CROSS_COMPILE = arm-linux-gnueabihf-

OUTPUT=my_driver
TARGET_IP = 192.168.1.57

obj-m := $(OUTPUT).o

KDIR := ~/linux_kernel

PWD := $(shell pwd)



default:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) modules
	$(CROSS_COMPILE)-gcc main.c -o $(OUTPUT)
clean:
	@rm *.ko *.mod.c *.mod.o Module.symvers modules.order
install:
	@scp $(OUTPUT).ko $(OUTPUT)  udooer@$(TARGET_IP):~	

