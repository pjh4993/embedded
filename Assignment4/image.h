#ifndef IMAGE_H
#define IMAGE_H
#include <stdlib.h>
#define imageWidth 50
#define imageHeight 50
#define IMG_SPD   5

#define SIZE_FONT 6
#define XLEN_FONT 6
#define YLEN_FONT 8

#define SIZE_SKKU 300
#define XLEN_SKKU 50
#define YLEN_SKKU 48

typedef struct image {
    unsigned char* data;
    unsigned int   xlen;
    unsigned int   ylen;
    unsigned int   xpos;
    unsigned int   ypos;
    int            xspd;
} img;
img* load_string(const char*, size_t);

#endif
