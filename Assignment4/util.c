#define S_WIDTH     128
#define S_HEIGHT    64
#define S_PAGES     (S_HEIGHT/8)

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <error.h>
#include <errno.h>
#include "image.h"
#include "util.h"
#define SSD1306_I2C_DEV 0x3C

#define CATCH()     {if(errno != 0x0){ printf("error : %s",strerror(errno)); errno=0;}}

void ssd1306_Init(int i2c_fd){
    ssd1306_command(i2c_fd, 0xA8);
    ssd1306_command(i2c_fd, 0x3f); //Set Mux Ratio
    
    ssd1306_command(i2c_fd, 0xD3); //Set Display offset
    ssd1306_command(i2c_fd, 0x00);

    ssd1306_command(i2c_fd, 0x40); //Set display start line

    ssd1306_command(i2c_fd, 0xA0); //Set segment remap
                                   //0xA1 for vertical inversion

    ssd1306_command(i2c_fd, 0xC0); //Set COM Output scan Direction
                                   //0xC8 for horizontal inversion

    ssd1306_command(i2c_fd, 0xDA); //Set COM pins hardware configuration
    ssd1306_command(i2c_fd, 0x12); //Manual says 0x2, but 0x12 is required

    ssd1306_command(i2c_fd, 0x81); //Set Contrast Control
    ssd1306_command(i2c_fd, 0x7F); //0:min, 0xFF:max

    ssd1306_command(i2c_fd, 0xA4); //Disable Entire Display on

    ssd1306_command(i2c_fd, 0xA6); //Set Normal Display

    ssd1306_command(i2c_fd, 0xD5); //Set Osc Frequency
    ssd1306_command(i2c_fd, 0x80);

    ssd1306_command(i2c_fd, 0x8D); //Enable charge pump regulator
    ssd1306_command(i2c_fd, 0x14);

    ssd1306_command(i2c_fd, 0xAF);
}

void ssd1306_command(int i2c_fd, uint8_t cmd){
    uint8_t buffer[2];
    buffer[0] = (0<<7) | (0<<6);
    buffer[1] = cmd;
    int len = write(i2c_fd, buffer, 2);
    CATCH();
}

void ssd1306_data(int i2c_fd, const uint8_t* data, size_t size){
    uint8_t* buffer = (uint8_t*)malloc(size+1);
    CATCH();
    buffer[0] = (0<<7) | (1<<6);
    memcpy(buffer + 1, data, size);
    if(write(i2c_fd, buffer, size+1) != size+1){
        printf("i2c write failed! in DATA\n");
    }
    free(buffer);
}

void update_area(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len, int mode){
    ssd1306_command(i2c_fd, 0x20);
    ssd1306_command(i2c_fd, mode);
    
    ssd1306_command(i2c_fd, 0x21);
    ssd1306_command(i2c_fd, x);
    ssd1306_command(i2c_fd, x + x_len - 1);

    ssd1306_command(i2c_fd, 0x22);
    ssd1306_command(i2c_fd, y);
    ssd1306_command(i2c_fd, y + y_len - 1);
    
    ssd1306_data(i2c_fd, data, x_len * y_len);
}

void paint_img(int i2c_fd, img* pimg){
    update_area_x_wrap(i2c_fd, pimg->data, pimg->xpos, (pimg->ypos)>>3, pimg->xlen, (pimg->ylen)>>3);
}

void update_area_x_wrap(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len){
    if(x + x_len <= S_WIDTH){
        update_area(i2c_fd ,data ,x ,y ,x_len ,y_len, 0x00);
    }else{
        int part1_len = S_WIDTH-x;
        int part2_len = x_len - part1_len;

        uint8_t* part1_buf = (uint8_t*)malloc(part1_len*y_len);
        uint8_t* part2_buf = (uint8_t*)malloc(part2_len*y_len);

        for(int x = 0; x < part1_len; x++) {
            for(int y = 0; y < y_len; y++) {
                part1_buf[y_len*x+y] = data[x_len*y+x];
            }
        }

        for(int x = 0; x < part2_len; x++) {
            for(int y = 0; y < y_len; y++) {
                part2_buf[y_len*x+y] = data[x_len*y+part1_len+x];
            }
        }
       update_area(i2c_fd, part1_buf, x, y,part1_len, y_len, 0x01);
       update_area(i2c_fd, part2_buf, 0, y-1 < 0?7:y-1,part2_len, y_len, 0x01);

       free(part1_buf);
       free(part2_buf);
    }
}
//front is moving, background is fixed.
void update_overlap(img * front, img * back){
    for (int x = front->xlen - front->xspd; x < front->xlen; x++) {
        //unit is 1pixel x 1page
        for (int y = 0; y < front->ylen; y += 8) {
            int xpos = (front->xpos + x) % S_WIDTH;
            int ypos = front->ypos + y;
            uint8_t overlap = 0; 
            //Check if target pos is in back image
            if((xpos >= back->xpos) && (xpos < back->xpos + back->xlen)
                && (ypos >= back->ypos) && (ypos < back->ypos + back->ylen)){
                //Set as backgroud image
                overlap = back->data[back->xlen * (ypos - back->ypos) / 8 + (xpos - back->xpos)];
                //overlap |= back->data[back->xlen * (ypos - back->ypos)/8 + (xpos - back->xpos)];
            }
            front->data[front->xlen * (y / 8) + x] = overlap;
        }
    }
}


void init_rend(Render *rend){
    memset(rend->curr, 0 , S_PAGES * S_WIDTH);
    memset(rend->effected, 0 , 8 * 16);
}

#define ABS(x) ((x < 0) ? -x : x)

void paint_rend_img(int i2c_fd, Render *rend, int ypos, int xpos){
    /*
    unsigned char *data = &(rend->curr[ypos * S_WIDTH + xpos*8]);
    update_area(i2c_fd ,data ,xpos * 8,ypos,8 , 1, 0x00);
    */
    update_area(i2c_fd ,rend->curr ,0, 0, 128, 8, 0x00);
}

void paint_rend(Render *rend, img* pimg){
    int i,j;
    int upperY = pimg->ypos / 8, seperate = pimg->ypos%8;
    int xlen = pimg->xlen, ylen = pimg->ylen, xpos = pimg->xpos, 
        xspd = pimg->xspd, yspd = pimg->yspd ,curPage, prevPage;
    unsigned char *data = pimg->data, *curr = rend->curr, 
        *effected = rend->effected ,tmp[xlen + ABS(xspd)], *src, *dst;
    unsigned char mask;
    int srcXst = (xspd > 0) ? ABS(xspd) : 0 , xblank = (xspd > 0) ? 0 : xlen;

    for (i=0; i<= ylen/8; i++){
        dst = &curr[xpos + (upperY + i) * S_WIDTH];
        memcpy(tmp, dst, xlen+ ABS(xspd));
        curPage = i*xlen;
        prevPage = (i-1)*xlen;
        if(seperate != 0){
            mask = -1;
            mask = mask >> seperate;
            mask = ~mask;
            if(prevPage >= 0){
                for(j=0; j<xlen; j++){
                    tmp[j + srcXst] |= (data[prevPage + j] & mask) >> (8 - seperate);
                }
            }
            mask = ~mask;
            for(j=0; j<xlen; j++){
                tmp[j + srcXst] |= (data[curPage + j] & mask) << seperate;
            }
            if(i == ylen/8)
                mask = (1 << seperate) -1;
            else if(i != 0)
                mask = -1;
            else
                mask = ~((1 << seperate) - 1);
            
            for(j=xblank; j<xspd; j++){
                tmp[j] = mask;
            }
           
            src = tmp;
        }else{
            src = &data[curPage];
        }
        
        memcpy(dst, src, xlen + ABS(xspd));
    }

    for(i=upperY; i<=upperY + ylen/8; i++){
        for(j=xpos/8; j<=(xpos + xlen)/8; j++){
            effected[j + i * 16] = 1;
        }
    }
}
