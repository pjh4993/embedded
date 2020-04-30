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
    int reg_id = gpio_nr / 32;
    int pos = gpio_nr % 32;

    #define GPIO_PUD_OFFSET 0x94
    #define GPIO_PUDCLK_OFFSET 0x98

    uint32_t* pud_reg = (uint32_t*) (gpio_ctr + GPIO_PUD_OFFSET);
    uint32_t* pudclk_reg = (uint32_t*) (gpio_ctr + GPIO_PUDCLK_OFFSET + 0x4 * reg_id);

    #define GPIO_PUD_PULLUP 0x2
    *pud_reg = GPIO_PUD_PULLUP;
    udelay(1);
    *pudclk_reg = (0x1 << pos);
    udelay(1);
    *pud_reg = 0;
    *pudclk_reg = 0;
}

void set_gpio_input(void *gpio_ctr, int gpio_nr) { 
	int reg_id = gpio_nr / 10; 
	int pos = gpio_nr % 10;
	uint32_t* fsel_reg = (uint32_t*) (gpio_ctr + 0x4 * reg_id);
	uint32_t fsel_val = *fsel_reg;
	uint32_t mask = 0x7 << (pos * 3);
	fsel_val = fsel_val & ~mask;
	*fsel_reg = fsel_val;
}

void get_gpio_input_value(void *gpio_ctr, int gpio_nr, int *value) { 
	int reg_id = gpio_nr / 32; 
	int pos = gpio_nr % 32;

	#define GPIO_LEV_OFFSET 0x34 

	uint32_t* level_reg = (uint32_t*) (gpio_ctr + GPIO_LEV_OFFSET + 0x4 * reg_id); 
	uint32_t level = *level_reg & (0x1 << pos);
	*value = level? 1:0;
}

void set_gpio_output(void *gpio_ctr, int gpio_nr) {
	int reg_id = gpio_nr / 10;
	int pos = gpio_nr % 10;

	uint32_t* fsel_reg = (uint32_t*) (gpio_ctr + 0x4 * reg_id);
	uint32_t fsel_val = *fsel_reg;
	uint32_t mask = 0x7 << (pos * 3);
	fsel_val = fsel_val & ~mask;
	uint32_t gpio_output_select = 0x1 << (pos * 3); 
	fsel_val = fsel_val | gpio_output_select;
	*fsel_reg = fsel_val;
}

void set_gpio_output_value(void *gpio_ctr, int gpio_nr, int value) {
	int reg_id = gpio_nr / 32;
	int pos = gpio_nr % 32;
    if(value) { 
        #define GPIO_SET_OFFSET 0x1c 
        uint32_t* output_set = (uint32_t*) (gpio_ctr + GPIO_SET_OFFSET + 0x4 * reg_id); *output_set = 0x1 << pos; 
    } else { 
        #define GPIO_CLR_OFFSET 0x28 
        uint32_t* output_clr = (uint32_t*) (gpio_ctr + GPIO_CLR_OFFSET + 0x4 * reg_id); *output_clr = 0x1 << pos; 
    }
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


	return 0;
}

char buff[32];

ssize_t rpikey_write(struct file *fp, const char __user * buffer, size_t size, loff_t * off) {
    size_t it;
    char * c;
	for (size_t it = 0; it < size; it++){
        int gpio13 = 0;//b
        int gpio19 = 0;//g
        int gpio26 = 0;//r

        get_user(c, buffer + it);
        
        if (*c == 'r') {
            gpio26 = 1;
        } else if (*c == 'g') {
            gpio19 = 1;
        } else if (*c == 'b') {
            gpio13 = 1;
        } else if (*c != 'o'){
            continue;
        }

        set_gpio_output_value(gpio_ctr, 13, gpio13);
        set_gpio_output_value(gpio_ctr, 19, gpio19);
        set_gpio_output_value(gpio_ctr, 26, gpio26);
        delay(1);
    }
    return 0;
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
