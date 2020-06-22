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

#define BTN_CNT 4
char btn_id[BTN_CNT+1];

ssize_t rpikey_read(struct file *fp, char __user * buffer, size_t size, loff_t * off) {
	btn_id[BTN_CNT] = '\0';
    copy_to_user(buffer, btn_id, BTN_CNT);
    memset(btn_id, 0, BTN_CNT);
    return BTN_CNT;
}
struct file_operations key_fops = {
    .open = rpikey_open,
    .read = rpikey_read,
    .release = rpikey_release,
};
typedef struct Device {
  int device_id;
}device;

#define MAJOR_NUM 0
#define DEVICE_NAME "rpikey"
#define CLASS_NAME DEVICE_NAME

#define PERIPHERAL_BASE 0x3F000000UL
#define GPIO_BASE (PERIPHERAL_BASE + 0x200000)

static unsigned int irq_gpio20 = 0, irq_gpio21 = 0;
static device dev_id_gpio20={.device_id = 20}, dev_id_gpio21={.device_id = 21};
static int majorNumber;
static struct class *cRpiKeyClass;


static irqreturn_t irq_handler(int irq, void *dev_id) {
    pr_info("irq handled %d\n",((device*)dev_id)->device_id);
    int id = ((device*)dev_id)->device_id;
    btn_id[id%20] = 1;
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

    gpio_request(20, "gpio20");
    gpio_request(21, "gpio21");

    gpio_direction_input(20);
    gpio_direction_input(21);

    irq_gpio20 = gpio_to_irq(20);
    irq_gpio21 = gpio_to_irq(21);

    gpio_ctr = ioremap(GPIO_BASE, 0x1000);

    set_gpio_pullup(gpio_ctr, 20);
    set_gpio_pullup(gpio_ctr, 21);

    int result_20 = request_irq(irq_gpio20, irq_handler, IRQF_SHARED | IRQF_TRIGGER_FALLING, "sw20",(void*)&dev_id_gpio20);
    int result_21 = request_irq(irq_gpio21, irq_handler, IRQF_SHARED | IRQF_TRIGGER_FALLING, "sw21",(void*)&dev_id_gpio21);

    pr_info("result of irq %d %d\n",result_20, result_21);

    return 0;
}

static void __exit rpikey_exit(void) {
    iounmap(gpio_ctr);

    gpio_free(20);
    gpio_free(21);

    if(irq_gpio20){
	pr_info("free irq 20 %d\n", irq_gpio20);
        free_irq(irq_gpio20, &dev_id_gpio20);
    }
    if(irq_gpio21){
	pr_info("free irq 21 %d\n", irq_gpio21);
        free_irq(irq_gpio21, &dev_id_gpio21);
    }


    device_destroy(cRpiKeyClass, MKDEV(majorNumber, 0));
    class_unregister(cRpiKeyClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
}

module_init(rpikey_init);
module_exit(rpikey_exit);
MODULE_LICENSE("GPL");
