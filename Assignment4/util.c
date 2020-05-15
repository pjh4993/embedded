#define S_WIDTH     128
#define S_HEIGHT    64
#define S_PAGES     (S_HEIGHT/8)

#include <stdlib.h>
#include <stdint.h>

void ssd1306_Init(int i2c_fd);
void ssd1306_command(int i2c_fd, uint8_t cmd);
void ssd1306_data(int i2c_fd, const uint8_t* data, size_t size);
void update_area(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len);
void update_area_x_wrap(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len);


void ssd1306_Init(int i2c_fd){

}

void ssd1306_command(int i2c_fd, uint8_t cmd){

}

void ssd1306_data(int i2c_fd, const uint8_t* data, size_t size){

}

void update_area(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len){

}

void update_area_x_wrap(int i2c_fd, const uint8_t* data, int x, int y, int x_len, int y_len){


}
