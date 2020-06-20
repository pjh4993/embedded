#include <stdio.h>
#include <stdlib.h>
#include "image.h"


const unsigned char font[96][6] = {
    {0x00,0x00,0x00,0x00,0x00,0x00}, //  
    {0x2e,0x00,0x00,0x00,0x00,0x00}, // !
    {0x06,0x00,0x06,0x00,0x00,0x00}, // "
    {0x14,0x3e,0x14,0x3e,0x14,0x00}, // #
    {0x04,0x2a,0x3e,0x2a,0x10,0x00}, // $
    {0x22,0x10,0x08,0x04,0x22,0x00}, // %
    {0x14,0x2a,0x2a,0x2c,0x10,0x28}, // &
    {0x06,0x00,0x00,0x00,0x00,0x00}, // '
    {0x1c,0x22,0x00,0x00,0x00,0x00}, // (
    {0x22,0x1c,0x00,0x00,0x00,0x00}, // )
    {0x14,0x08,0x14,0x00,0x00,0x00}, // *
    {0x08,0x1c,0x08,0x00,0x00,0x00}, // +
    {0x60,0x00,0x00,0x00,0x00,0x00}, // ,
    {0x08,0x08,0x08,0x00,0x00,0x00}, // -
    {0x20,0x00,0x00,0x00,0x00,0x00}, // .
    {0x30,0x0c,0x02,0x00,0x00,0x00}, // /
    {0x1c,0x22,0x22,0x22,0x1e,0x00}, // 0
    {0x02,0x3e,0x00,0x00,0x00,0x00}, // 1
    {0x32,0x2a,0x2a,0x24,0x00,0x00}, // 2
    {0x2a,0x2a,0x2a,0x16,0x00,0x00}, // 3
    {0x0e,0x10,0x10,0x3e,0x10,0x00}, // 4
    {0x2e,0x2a,0x2a,0x12,0x00,0x00}, // 5
    {0x3c,0x2a,0x2a,0x2a,0x12,0x00}, // 6
    {0x06,0x02,0x22,0x12,0x0e,0x00}, // 7
    {0x14,0x2a,0x2a,0x2a,0x16,0x00}, // 8
    {0x04,0x2a,0x2a,0x2a,0x1e,0x00}, // 9
    {0x24,0x00,0x00,0x00,0x00,0x00}, // :
    {0x64,0x00,0x00,0x00,0x00,0x00}, // ;
    {0x08,0x14,0x22,0x00,0x00,0x00}, // <
    {0x14,0x14,0x14,0x00,0x00,0x00}, // =
    {0x22,0x14,0x08,0x00,0x00,0x00}, // >
    {0x02,0x2a,0x0a,0x04,0x00,0x00}, // ?
    {0x3c,0x02,0x1a,0x2a,0x22,0x1e}, // @
    {0x3c,0x12,0x12,0x12,0x3e,0x00}, // A
    {0x3c,0x2a,0x2a,0x2e,0x10,0x00}, // B
    {0x1c,0x22,0x22,0x22,0x00,0x00}, // C
    {0x3c,0x22,0x22,0x22,0x1c,0x00}, // D
    {0x3c,0x2a,0x2a,0x2a,0x00,0x00}, // E
    {0x3c,0x12,0x12,0x12,0x00,0x00}, // F
    {0x3c,0x22,0x22,0x2a,0x1a,0x00}, // G
    {0x3e,0x08,0x08,0x3e,0x00,0x00}, // H
    {0x22,0x3e,0x22,0x00,0x00,0x00}, // I
    {0x30,0x22,0x22,0x1e,0x00,0x00}, // J
    {0x3e,0x08,0x0c,0x32,0x00,0x00}, // K
    {0x3e,0x20,0x20,0x20,0x00,0x00}, // L
    {0x3c,0x02,0x02,0x3c,0x02,0x02}, // M
    {0x3c,0x02,0x02,0x02,0x3e,0x00}, // N
    {0x1c,0x22,0x22,0x22,0x1e,0x00}, // O
    {0x3c,0x12,0x12,0x12,0x0e,0x00}, // P
    {0x1c,0x22,0x22,0x62,0x1e,0x00}, // Q
    {0x3c,0x12,0x12,0x32,0x0e,0x00}, // R
    {0x24,0x2a,0x2a,0x12,0x00,0x00}, // S
    {0x02,0x02,0x3e,0x02,0x02,0x00}, // T
    {0x1e,0x20,0x20,0x20,0x1e,0x00}, // U
    {0x0e,0x10,0x20,0x10,0x0e,0x00}, // V
    {0x3e,0x20,0x20,0x1e,0x20,0x20}, // W
    {0x36,0x08,0x08,0x36,0x00,0x00}, // X
    {0x26,0x28,0x28,0x1e,0x00,0x00}, // Y
    {0x32,0x2a,0x2a,0x26,0x00,0x00}, // Z
    {0x3e,0x22,0x00,0x00,0x00,0x00}, // [
    {0x02,0x0c,0x30,0x00,0x00,0x00}, // "\"
    {0x22,0x3e,0x00,0x00,0x00,0x00}, // ]
    {0x04,0x02,0x04,0x00,0x00,0x00}, // ^
    {0x20,0x20,0x20,0x00,0x00,0x00}, // _
    {0x02,0x04,0x00,0x00,0x00,0x00}, // `
    {0x3c,0x12,0x12,0x12,0x3e,0x00}, // a
    {0x3c,0x2a,0x2a,0x2e,0x10,0x00}, // b
    {0x1c,0x22,0x22,0x22,0x00,0x00}, // c
    {0x3c,0x22,0x22,0x22,0x1c,0x00}, // d
    {0x3c,0x2a,0x2a,0x2a,0x00,0x00}, // e
    {0x3c,0x12,0x12,0x12,0x00,0x00}, // f
    {0x3c,0x22,0x22,0x2a,0x1a,0x00}, // g
    {0x3e,0x08,0x08,0x3e,0x00,0x00}, // h
    {0x22,0x3e,0x22,0x00,0x00,0x00}, // i
    {0x30,0x22,0x22,0x1e,0x00,0x00}, // j
    {0x3e,0x08,0x0c,0x32,0x00,0x00}, // k
    {0x3e,0x20,0x20,0x20,0x00,0x00}, // l
    {0x3c,0x02,0x02,0x3c,0x02,0x02}, // m
    {0x3c,0x02,0x02,0x02,0x3e,0x00}, // n
    {0x1c,0x22,0x22,0x22,0x1e,0x00}, // o
    {0x3c,0x12,0x12,0x12,0x0e,0x00}, // p
    {0x1c,0x22,0x22,0x62,0x1e,0x00}, // q
    {0x3c,0x12,0x12,0x32,0x0e,0x00}, // r
    {0x24,0x2a,0x2a,0x12,0x00,0x00}, // s
    {0x02,0x02,0x3e,0x02,0x02,0x00}, // t
    {0x1e,0x20,0x20,0x20,0x1e,0x00}, // u
    {0x0e,0x10,0x20,0x10,0x0e,0x00}, // v
    {0x3e,0x20,0x20,0x1e,0x20,0x20}, // w
    {0x36,0x08,0x08,0x36,0x00,0x00}, // x
    {0x26,0x28,0x28,0x1e,0x00,0x00}, // y
    {0x32,0x2a,0x2a,0x26,0x00,0x00}, // z
    {0x08,0x3e,0x22,0x00,0x00,0x00}, // {
    {0x3e,0x00,0x00,0x00,0x00,0x00}, // |
    {0x22,0x3e,0x08,0x00,0x00,0x00}, // }
    {0x04,0x02,0x02,0x00,0x00,0x00}, // ~
    {0x00,0x00,0x00,0x00,0x00,0x00}
};

const unsigned char skku []={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,
    0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFC,0xDC,0x5C,0xFC,0xFC,0xFC,0xFC,0x1C,0x1C,0x1C,
    0x1C,0x18,0xB8,0xB8,0xF0,0xF0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFB,0xC1,0x00,0x01,0x07,0xC3,0xF1,0xFC,
    0xFE,0xFE,0x1F,0x07,0x03,0x03,0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0x3F,0x3F,0x3B,0x31,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x03,
    0x1F,0x7F,0xFF,0xFF,0xF8,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,
    0xFF,0x3F,0x1F,0x1F,0x8F,0xC6,0xC6,0xE0,0x70,0x70,0x38,0x18,0x0C,0x0C,0x04,0x04,
    0x02,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x7F,0xFE,0xFC,0xF8,0xE0,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
    0x0F,0x3F,0x7F,0xFF,0xFE,0x7F,0x1F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC1,0xFF,0xFF,
    0x7F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x0E,0x1F,0x1E,0x3C,
    0x3C,0x38,0x38,0x70,0x70,0x70,0x70,0x70,0x70,0x30,0x38,0x38,0x1C,0x1E,0x0F,0x07,
    0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const unsigned char display_00 []=
{
0xE0, 0xC0, 0x8C, 0x1C, 0x3C, 0x7C, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 
0x1C, 0x8C, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x87, 
0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC3, 0xF1, 0xF8, 0xFC, 0xFE, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x07, 0x0F, 0xCF, 0xCF, 
0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x0F, 0x07, 0xE3, 0xF1, 
0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0x7F, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 
0xFC, 0xF8, 0xF1, 0xF3, 0xE3, 0xE7, 0xC0, 0xC0, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
};

const unsigned char display_04 []=
{
0xFC, 0xF8, 0xF0, 0xE0, 0xC4, 0x8C, 0x1C, 0x3C, 0x7C, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 
0x1C, 0x8C, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xEC, 0x8E, 
0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC3, 0xF1, 0xF8, 0xFC, 0xFE, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x07, 0x0F, 0xCF, 0xCF, 
0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x0F, 0x07, 0xE3, 0xF1, 
0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0x7F, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 
0xFC, 0xF8, 0xF1, 0xF3, 0xE3, 0xE7, 0xC0, 0xC0, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
};

const unsigned char display_07 [] =
{
0xE0, 0xC0, 0x8C, 0x1C, 0x3C, 0x7C, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 
0x1C, 0x8C, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x87, 
0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC3, 0xF1, 0xF8, 0xFC, 0xFE, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF9, 0xFE, 0x7C, 0xF8, 0xF1, 0xE3, 
0xC7, 0x8F, 0x0F, 0x0F, 0x4F, 0xCF, 0x0F, 0x07, 0xE3, 0xF1, 
0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC7, 0x8F, 
0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0x7F, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x03, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x3F, 
0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 
0xFC, 0xF8, 0xF1, 0xF3, 0xE3, 0xE7, 0xC0, 0xC0, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
0xFC, 0xF8, 0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x3F, 0x7F, 0xFF, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x02
};


const unsigned char display_11 []=
{
0xE0, 0xC0, 0x8C, 0x1C, 0x3C, 0x7C, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 
0x1C, 0x8C, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x87, 
0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC3, 0xF1, 0xF8, 0xFC, 0xFE, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x07, 0x0F, 0xCF, 0xCF, 
0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x0F, 0x07, 0xE3, 0xF1, 
0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0x7F, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFC, 0xF8, 0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x3F, 
0x7F, 0x7F, 0x3F, 0x1F, 0x8F, 0xC7, 0xE3, 0xF1, 0xF8, 0xFC, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 
0xFC, 0xF8, 0xF1, 0xF3, 0xE3, 0xE7, 0xC0, 0xC0, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC7, 0xE3, 0xF0, 
0xF8, 0xF8, 0xF0, 0xE3, 0xC7, 0x8F, 0x1F, 0x3F, 0x7F, 0xFF, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00
};

const unsigned char display_18 []=
{
0xE0, 0xC0, 0x8C, 0x1C, 0x3C, 0x7C, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 
0x1C, 0x8C, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x87, 
0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC3, 0xF1, 0xF8, 0xFC, 0xFE, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x07, 0x0F, 0xCF, 0xCF, 
0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x0F, 0x07, 0xE3, 0xF1, 
0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0x7F, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x3F, 
0x7F, 0x7F, 0x3F, 0x1F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 
0xFC, 0xF8, 0xF1, 0xF3, 0xE3, 0xE7, 0xC0, 0xC0, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x8F, 0xC7, 0xE3, 0xF0, 
0xF8, 0xF8, 0xF0, 0xE3, 0xC7, 0x8F, 0x1F, 0x3F, 0x7F, 0xFF, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00
};

const unsigned char display_20 [] =
{
0xE0, 0xC0, 0x8C, 0x1C, 0x3C, 0x7C, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 
0x1C, 0x8C, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x87, 
0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC3, 0xF1, 0xF8, 0xFC, 0xFE, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x07, 0x0F, 0xCF, 0xCF, 
0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x0F, 0x07, 0xE3, 0xF1, 
0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0x7F, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFB, 0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x3F, 
0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 
0xFC, 0xF8, 0xF1, 0xF3, 0xE3, 0xE7, 0xC0, 0xC0, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
0xFC, 0xF8, 0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x3F, 0x7F, 0xFF, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x02
};

const unsigned char display_25 [] =
{
0xE0, 0xC0, 0x8C, 0x1C, 0x3C, 0x7C, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x3C, 
0x1C, 0x8C, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x87, 
0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0x7F, 0x3F, 0x1F, 0x8F, 0xC3, 0xF1, 0xF8, 0xFC, 0xFE, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFE, 0xFC, 0xF8, 0xF1, 0xE3, 0x07, 0x0F, 0xCF, 0xCF, 
0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x0F, 0x07, 0xE3, 0xF1, 
0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0x7F, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 
0xFC, 0xF8, 0xF1, 0xF3, 0xE3, 0xE7, 0xC0, 0xC0, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
};


img img_skku = {
    skku,
    XLEN_SKKU,
    YLEN_SKKU,
    70,
    0,
    IMG_SPD
};

img img_ani = {
    display_00,
    imageWidth,
    imageHeight,
    0,
    0,
    2,
    1
};

img* pimg_skku = &img_skku;
img* pimg_ani = &img_ani;
unsigned const char *ani_set[] = {display_00, display_04, display_07 ,display_11, display_18,display_20, display_25};

img* load_string(const char* str, size_t n) {
    unsigned int i, j;
    img* img_str = (img*)malloc(sizeof(img));
    img_str->data = (unsigned char*)malloc(n*SIZE_FONT+IMG_SPD);
    img_str->xlen = n*XLEN_FONT + IMG_SPD;
    img_str->ylen = YLEN_FONT;
    img_str->xpos = 0;
    img_str->ypos = 0;
    img_str->xspd = IMG_SPD;

    for(i=0; i<n; ++i) {
        for(j=0; j<XLEN_FONT; ++j) {
            if(str[i]-32>=0 && str[i]-32<96){
                img_str->data[i*XLEN_FONT+j] = font[str[i]-32][j];
            }else if(str[i] == 0){
                img_str->data[i*XLEN_FONT+j] = font[0][j];
            }else {
                fprintf(stderr, "Wrong character %c(%d)\n", str[i], str[i]);
                exit(1);
            }
        }
    }
    return img_str;
}
