#define PERIPHERAL_BASE 0x3F000000UL
#define GPIO_BASE (PERIPHERAL_BASE + 0x200000)
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

void set_gpio_output(void*, int);
void set_gpio_output_value(void*, int, int);
void set_gpio_input(void *, int);
void get_gpio_input_value(void *, int , int *);
void set_gpio_pullup(void *, int);

int main() {
    int fdmem = open("/dev/mem", O_RDWR);
    if(fdmem<0) {
        printf("Error opening /dev/mem");
        return -1;
    }

    void* gpio_ctr = mmap(0, 4096, PROT_READ+PROT_WRITE, MAP_SHARED, fdmem, GPIO_BASE);
    if(gpio_ctr==MAP_FAILED) {
        printf("mmap error ");
        return -1;
    }

    set_gpio_output(gpio_ctr, 13);
    set_gpio_output(gpio_ctr, 19);
    set_gpio_output(gpio_ctr, 26);
    
    set_gpio_output_value(gpio_ctr, 19, 0);
    set_gpio_output_value(gpio_ctr, 13, 0);
    set_gpio_output_value(gpio_ctr, 26, 0);

    munmap(gpio_ctr, 4096);
    close(fdmem);
}
