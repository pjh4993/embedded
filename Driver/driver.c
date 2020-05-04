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


void* gpio_ctr = NULL;

void set_gpio_pullup(void *gpio_ctr, int gpio_nr) {
    int reg_id = gpio_nr / 32;
    int pos = gpio_nr % 32;

#define GPIO_PUD_OFFSET 0x94
#define GPIO_PUDCLK_OFFSET 0x98
    uint32_t *pud_reg = (uint32_t*) (gpio_ctr + GPIO_PUD_OFFSET);
    uint32_t* pudclk_reg = (uint32_t*) (gpio_ctr + GPIO_PUDCLK_OFFSET + 0x4 * reg_id);

#define GPIO_PUD_PULLUP 0x2
    *pud_reg = GPIO_PUD_PULLUP;
    udelay(1);
    *pudclk_reg = (0x1 << pos);
    udelay(1);
    *pud_reg = 0;
    *pudclk_reg = 0;
}


static int rpikey_open(struct inode *inode, struct file *file) {
    return 0;
}

static int rpikey_release(struct inode *inode, struct file *file) {
    return 0;
}

//일단 ppt 복붙
long rpikey_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param) {
    if (ioctl_num == 101){//write
        uint32_t param_value[2]; 
        param_value[0] = gpio_get_value(20); 
        param_value[1] = gpio_get_value(21);
        copy_to_user((void*) ioctl_param, (void*) param_value, sizeof(uint32_t)*2);
    }
    
    if (ioctl_num == 100){//read
        uint32_t param_value[3];
        int gpio13;
        int gpio19;
        int gpio26;

        copy_from_user((void*) param_value, (void*) ioctl_param, sizeof(uint32_t)*3);

        gpio13 = (int)param_value[0];
        gpio19 = (int)param_value[1];
        gpio26 = (int)param_value[2];

        gpio_set_value(13,gpio13);
        gpio_set_value(19,gpio19);
        gpio_set_value(26,gpio26);
    }
    return 0;
}

char buf[1024];
int buf_btm = 0;
int buf_top = 0;

ssize_t rpikey_read(struct file *fp, char __user * buffer, size_t size, loff_t * off) {
    size_t left;
    size_t top_sz;
    size_t btm_sz;
    int top;
   
    top = buf_top;
    left = size;
    top_sz = (top > buf_btm ? top : 1024) - buf_btm;
    btm_sz = (top > buf_btm ? 0 : top);

    if (top_sz > 0){
        top_sz = (top_sz > left ? left : top_sz);
        copy_to_user(buf + buf_btm, buffer, top_sz);
        buf_btm = (buf_btm + top_sz) & 1023;
        left = size - top_sz;
    }

    if (btm_sz > 0){
        btm_sz = (btm_sz > left ? left : btm_sz);
        copy_to_user(buf + buf_btm, buffer, btm_sz);
        buf_btm = (buf_btm + btm_sz) & 1023;
    }
    return top_sz + btm_sz;
}

ssize_t rpikey_write(struct file *fp, const char __user * buffer, size_t size, loff_t * off) {
	size_t it=0;
    char user_buffer[size];
    pr_info("size of input %d",size);
    //fail to read from user space
    if(copy_from_user((void*)user_buffer, (void*)buffer, size))
        return -EFAULT;

    int gpio13, gpio19, gpio26;
    for (it = 0; it < size; it++){
	    gpio13 = 0;//b
	    gpio19 = 0;//g
	    gpio26 = 0;//r
	    char c = user_buffer[it];

	    if (c == 'r') {
		    gpio26 = 1;
	    } else if (c == 'g') {
		    gpio19 = 1;
	    } else if (c == 'b') {
		    gpio13 = 1;
	    } else if (c != 'o'){
		    continue;
	    }

	    gpio_set_value(13, gpio13);
	    gpio_set_value(19, gpio19);
	    gpio_set_value(26, gpio26);
	    udelay(1000);
    }
    return size - it;
}

struct file_operations key_fops = {
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

static unsigned int irq_gpio20 = 0, irq_gpio21 = 0;
static void *dev_id_gpio20, *dev_id_gpio21;
static int majorNumber;
static struct class *cRpiKeyClass;


static irqreturn_t irq_handler(unsigned int irq, void *dev_id) {
    if(dev_id == dev_id_gpio20)
        buf[buf_top] = '0';
    else
        buf[buf_top] = '1';
    buf_top = (buf_top + 1) & 1023;
    return IRQ_HANDLED;
}

static int __init rpikey_init(void) {
    pr_info("rpikey module installed\n");

    majorNumber = register_chrdev(MAJOR_NUM, DEVICE_NAME, &key_fops);
    if(majorNumber < MAJOR_NUM) {
        pr_alert("rpikey Failed to register a major number\n");
        return majorNumber;
    }

    cRpiKeyClass = class_create(THIS_MODULE, CLASS_NAME);
    device_create(cRpiKeyClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);

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

    request_irq(irq_gpio20, irq_handler, IRQF_SHARED | IRQF_TRIGGER_FALLING, "sw20", dev_id_gpio20);
    request_irq(irq_gpio21, irq_handler, IRQF_SHARED | IRQF_TRIGGER_FALLING, "sw21", dev_id_gpio21);

    return 0;
}

static void __exit rpikey_exit(void) {
    iounmap(gpio_ctr);

    if(irq_gpio20){
	pr_info("free irq 20");
        free_irq(irq_gpio20, dev_id_gpio20);
        irq_gpio20 = 0;
    }
    if(irq_gpio21){
	pr_info("free irq 21");
        free_irq(irq_gpio21, dev_id_gpio21);
        irq_gpio21 = 0;
    }

    gpio_free(13);
    gpio_free(19);
    gpio_free(26);
    gpio_free(20);
    gpio_free(21);

    device_destroy(cRpiKeyClass, MKDEV(majorNumber, 0));
    class_unregister(cRpiKeyClass);
    class_destroy(cRpiKeyClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
}

module_init(rpikey_init);
module_exit(rpikey_exit);
MODULE_LICENSE("GPL");
