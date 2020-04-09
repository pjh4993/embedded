#define PERIPHERAL_BASE 0x3F000000UL
#define GPIO_BASE (PERIPHERAL_BASE + 0x200000)
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define BLUE 13
#define GREEN 19
#define RED 26

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

    set_gpio_input(gpio_ctr, 4);
    set_gpio_pullup(gpio_ctr, 4);

    int clock[3] = {1, 0, 0};
    int gpio_4_value = 0;
    uint32_t cnt = 0;
    while(1) {
        set_gpio_output_value(gpio_ctr, BLUE, clock[(cnt+1)%3]);
        set_gpio_output_value(gpio_ctr, GREEN, clock[(cnt+2)%3]);
        set_gpio_output_value(gpio_ctr, RED, clock[(cnt)%3]);
        //스위치가 떨어질떄까지 루프
        while(!gpio_4_value)
            get_gpio_input_value(gpio_ctr, 4, &gpio_4_value);
        printf("switch detached\n");
        //스위치가 눌릴때까지 루프
        while(gpio_4_value)
            get_gpio_input_value(gpio_ctr, 4, &gpio_4_value);
        printf("switch attached\n");
        printf("---------------------------\n");
        //스위치 민감도 조절
        usleep(300000);
        cnt += 1;
    }

    munmap(gpio_ctr, 4096);
    close(fdmem);
}
