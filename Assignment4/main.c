#define S_WIDTH     128
#define S_HEIGHT    64
#define S_PAGES     (S_HEIGHT/8)

#include "skku.h"
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

uint8_t* data_s;
int I2C_FD;

void ssd1306_Init(int i2c_fd);
void ssd1306_command(int i2c_fd, uint8_t cmd);
void ssd1306_data(int i2c_fd, const uint8_t* data, size_t size);
void update_area(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len);
void update_area_x_wrap(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len);



void handler(int sig) {
    static int i = 0; 
    update_area_x_wrap(I2C_FD,data_s,i,LOGO_Y_LOCATION,LOGO_WIDTH+LOGO_MOVE,LOGO_HEIGHT);
    i+=LOGO_MOVE; 
    if(i>=S_WIDTH)i=0;
}

int main() {
    int I2C_FD = open("/dev/i2c-1",O_RDWR);
    if(I2C_FD < 0) { 
        printf("err opening device\n"); 
        return -1; 
    }
    if(ioctl(I2C_FD, I2C_SLAVE, SSD1306_I2C_DEV) < 0) { 
        printf("err setting i2c slave address\n"); 
        return -1; 
    }

    ssd1306_Init(I2C_FD);

    uint8_t* data_i = (uint8_t*) malloc(S_WIDTH*S_PAGES*NUM_FRAMES);

    for(int i = 0; i < NUM_FRAMES; i ++) {
        for(int x = 0; x <LOGO_WIDTH ; x++) { 
            for(int y = 0; y < LOGO_HEIGHT; y++) { 
                int target_x = (i*LOGO_MOVE +x) % S_WIDTH; 
                data[S_WIDTH*S_PAGES*i + S_WIDTH*(y+LOGO_Y_LOC)+ target_x] = skku[LOGO_WIDTH*y+x]; 
            } 
        } 
    };
    
    update_area(I2C_FD, data_i, 0, 0, 128, 64);
    free(data_i);

    data_s = (uint8_t*)malloc((LOGO_WIDTH+LOGO_MOVE)*LOGO_HEIGHT);
    for(int y = 0; y < LOGO_HEIGHT; y++) { 
        for(int x = 0; x < LOGO_MOVE ; x++) { 
            data_s[(LOGO_WIDTH+LOGO_MOVE)*y+x] = 0x0; 
        } 
        for(int x = 0; x < LOGO_WIDTH ; x++) {
            data_s[(LOGO_WIDTH+LOGO_MOVE)*y+(x+LOGO_MOVE)] = skku[LOGO_WIDTH*y+x]; 
        }
    }

    signal(SIGALRM, handler);
    ualarm(20000, 20000);

    while(1){
        sleep(1);
    }
    
    free(data_s);
    close(I2C_FD); 
    return 0;
}
