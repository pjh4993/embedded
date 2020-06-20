#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>
#include "image.h"
void ssd1306_Init(int i2c_fd);
void ssd1306_command(int i2c_fd, uint8_t cmd);
void ssd1306_data(int i2c_fd, const uint8_t* data, size_t size);
void update_area(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len, int mode);
void update_area_x_wrap(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len);
void paint_img(int i2c_fd, img* pimg);
void update_overlap(img * front, img * back);

typedef struct renderer{
    unsigned char curr[S_WIDTH * S_PAGES];
    unsigned char effected[8 * 16];
} Render;


void paint_rend(Render *rend, img* pimg);
void paint_rend_img(int i2c_fd, Render *rend, int ypos, int xpos);
void init_rend(Render* rend);
#endif
