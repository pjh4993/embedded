#ifndef IMAGE_H
#define IMAGE_H

#define IMG_SPD   5

#define SIZE_FONT 6
#define XLEN_FONT 6
#define YLEN_FONT 8

#define SIZE_SKKU 300
#define XLEN_SKKU 50
#define YLEN_SKKU 48

#include <stdio.h>
#include <stdlib.h>

typedef struct image {
    unsigned char* data;
    unsigned int   xlen;
    unsigned int   ylen;
    unsigned int   xpos;
    unsigned int   ypos;
    int            xspd;
} img;

img img_skku = {
    skku,
    XLEN_SKKU,
    YLEN_SKKU,
    32,
    0,
    IMG_SPD
};

img* pimg_skku = &img_skku;

img* load_string(const char*, size_t);

#endif
