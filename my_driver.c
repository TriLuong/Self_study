#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h> 
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/cdev.h>

static char command[256];
static char response[256];
int have_command = 0;


#define My_Print 'P'
#define Print_Hi _IOWR(My_Print, 10, unsigned long)
#define Print_Bye _IOWR(My_Print, 11, unsigned long)

static long my_ioctl(struct file *f, unsigned int cmd, unsigned long lArg)
{
	int retval;

	// unsigned long *arg = (unsigned long *)lArg;

	switch(cmd){
		case Print_Hi:
			printk("Xin Chao!\n");
			break;
		case Print_Bye:
			printk("Tam biet!\n");
			break;
		default:
			printk("ERROR: please type again\n");
			retval = -EINVAL;
			break;
	}	
	return retval;
}

int my_read(struct file *f, char *buffer, size_t count, loff_t *offp)
{
	int ret;

	if(0==have_command)
		return 0;

	if(count > strlen(response))
		count = strlen(response);


	ret = copy_to_user(buffer, response, strlen(response));
	if(ret != 0)
		return -EINVAL;

	have_command = 0;

	return count;
}

int my_write(struct file *f, const char *buffer, size_t count, loff_t *offp)
{
	int ret;

	if (count > sizeof(command)-1)
		count = sizeof(command)-1;

	ret = copy_from_user(command, buffer, count);

	if(ret != 0)
		return -EINVAL;

	command[count] = '\0';

	switch(command[0])
	{
		case 's':
			strcpy(response, "OK\n");
			break;
		case 'c':
			strcpy(response, "OK\n");
			break;
		default:
			strcpy(response, "ERROR!!!");
	}

	return count;
}

static struct file_operations my_fops =
{
	.unlocked_ioctl = my_ioctl,
	.read = my_read,
	.write = my_write,
};

static dev_t my_device;
static struct cdev c_dev;
static struct class *cl;

static int __init my_init(void)
{
	int ret;
	// int rc;

	printk(KERN_INFO "[INFO]:\tmy_driver: init!!!\n");

	/*Create major number*/
	if((ret = alloc_chrdev_region(&my_device,0,1,"My_device_1")) < 0){
		printk(KERN_DEBUG "[ERROR] registing device\n");
		return ret;
	}

	/*Create class*/
	if((cl = class_create(THIS_MODULE, "my_device_1_class")) == NULL){
		unregister_chrdev_region(my_device, 1);
		return -1;
	}

	/*Create device*/
	if((device_create(cl, NULL, my_device, NULL, "my_device_1_device")) == NULL){
		class_destroy(cl);
		unregister_chrdev_region(my_device, 1);
		return -1;
	}

	cdev_init(&c_dev, &my_fops);
	if(cdev_add(&c_dev, my_device, 1) == 1){
		device_destroy(cl, my_device);
		class_destroy(cl);
		unregister_chrdev_region(my_device,1);
		return -1;
	}

	return 0;
}

static void __exit my_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cl, my_device);
	class_destroy(cl);
	unregister_chrdev_region(my_device,0);
	printk(KERN_INFO "[INFO] my driver exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Tri Luong");
MODULE_DESCRIPTION("Hello, This is My First Module");