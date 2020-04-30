#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <asm/io.h>

MODULE_LICENCE("GPL");

void* gpio_ctr = NULL;

void set_gpio_pullup(void *gpio_ctr, int gpio_nr) {
}

static int rpikey_open(struct inode *inode, struct file *file) {
    return 0;
}

static int rpikey_release(struct inode *inode, struct file *file) {
    return 0;
}

long rpikey_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param) {
    //??
}

ssize_t rpikey_read(struct file *fp, char __user * buffer, size_t size, loff_t * off) {
    //??
}

ssize_t rpikey_write(struct file *fp, const char __user * buffer, size_t size, loff_t * off) {
    //??
}

struct file_operations Fops = {
    .unlocked_ioctl = rpikey_ioctl,
    .open = rpikey_open,
    .read = rpikey_read,
    .write = rpikey_write, 
    .release = rpikey_release,
};

#define MAJOR_NUM 0
#define DEVICE_NAME "rpikey"
#define CLASS_NAME DEVICE_NAME

#define PERIPHERAL_BASE 0x3F000000UL
#define GPIO_BASE (PERIPHERAL_BASE + 0x200000)

static int majorNumber;
static struct class* cRpiKeyClass = NULL;
static struct device* cRpiKeyDevice = NULL;

static int __init rpikey_init(void) {
    pr_info("rpikey module installed\n");

    majorNumber = register_chrdev(MAJOR_NUM, DEVICE_NAME, &key_fops);
    if(majorNumber < MAJOR_NUM) {
        pr_alert("rpikey Failed to register a major number\n");
        return majorNumber;
    }

    cRpiKeyClass = class_create(THIS_MODULE, CLASS_NAME);
    cRpiKeyDevice = device_create(cRpiKeyClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);

    gpio_request(13, "gpio13");
    gpio_request(19, "gpio19");
    gpio_request(26, "gpio26");
    gpio_request(20, "gpio20");
    gpio_request(21, "gpio21");

    gpio_direction_output(13, 0);
    gpio_direction_output(19, 0);
    gpio_direction_output(26, 0);

    gpio_direction_input(20);
    gpio_direction_input(21);

    irq_gpio20 = gpio_to_irq(20);
    irq_gpio21 = gpio_to_irq(21);

    gpio_ctr = ioremap(GPIO_BASE, 0x1000);

    set_gpio_pullup(gpio_ctr, 20);
    set_gpio_pullup(gpio_ctr, 21);

    //??

    return 0;
}

static void __exit rpikey_exit(void) {
    iounmap(gpio_ctr);

    //??

    gpio_free(13);
    gpio_free(19);
    gpio_free(26);
    gpio_free(20);
    gpio_free(21);

    device_destroy(cRpiKeyClass, MKDEV(majorNumber, 0));
    class_unregiser(cRpiKeyClass);
    class_destroy(cRpiKeyClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
}

module_init(rpikey_init);
module_exit(rpikey_exit);

/*
long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param) {
    if(ioctl_num == 100) {
        uint32_t param_value[2];
        param_value[0] = gpio_get_value(20);
        param_value[1] = gpio_get_value(21);

        copy_to_user((void*)ioctl_param, (void*)param_value, sizeof(uint32_t)*2);
    }

    if(ioctl_num == 101) {
        uint32_t param_value[3];
        int gpio13, gpio19, gpio26;

        copy_from_user((void*)param_value, (void*)ioctl_param, sizeof(uint32_t)*3);

        gpio13 = (int)param_value[0];
        gpio19 = (int)param_value[1];
        gpio26 = (int)param_value[2];

        gpio_set_value(13, gpio13);
        gpio_set_value(19, gpio19);
        gpio_set_value(26, gpio26);
    }

    return 0;
}
*/
