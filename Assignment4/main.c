#define S_WIDTH     128
#define S_HEIGHT    64
#define S_PAGES     (S_HEIGHT/8)
#define LOGO_MOVE 4
#define NUM_FRAMES (S_WIDTH/LOGO_MOVE) 
#define LOGO_Y_LOC 1

#include "image.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <signal.h>

#define SSD1306_I2C_DEV 0x3C

int I2C_FD;
img* p_img_str;
unsigned char zero[2 * imageHeight];
img blank_img = {zero, 2 , imageHeight,0,0,0};
extern img* pimg_skku;
extern img* pimg_ani;
extern unsigned char *ani_set[];

void handler(int sig) {
    static int i = 0; 
    static int j = 1;
    static unsigned char *prev = NULL;
    int ti, tj;
    printf("%d\n",blank_img.xpos);
    blank_img.xpos = (pimg_ani->xpos!=0) ? pimg_ani->xpos - 2 : 0;
    paint_img(I2C_FD, &blank_img);
    
    
    if(prev != NULL){


        }
    }
    paint_img(I2C_FD, pimg_ani);
    prev = pimg_ani->data;
    i++;
    pimg_ani->data = ani_set[i%7];
    pimg_ani->xpos += 2;
    
    if(pimg_ani->xpos > 70)
        pimg_ani->xpos = 0;
        blank_img.xpos = 0;

}

int main() {
    I2C_FD = open("/dev/i2c-1",O_RDWR);
    printf("I2C_FD %d\n",I2C_FD);
    if(I2C_FD < 0) { 
        printf("err opening device\n"); 
        return -1; 
    }
    if(ioctl(I2C_FD, I2C_SLAVE, SSD1306_I2C_DEV) < 0) { 
        printf("err setting i2c slave address\n"); 
        return -1; 
    }

    ssd1306_Init(I2C_FD);
    paint_img(I2C_FD, &blank_img);
    paint_img(I2C_FD, pimg_skku);
    p_img_str = load_string("SKKU GYUL",sizeof("SKKU GYUL"));
    p_img_str->xpos=S_WIDTH;
    

    while(1){
        usleep(20000);
        handler(0);
    }
    
    close(I2C_FD); 
    return 0;
}
