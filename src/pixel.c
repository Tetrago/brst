#include "pixel.h"

void pixel_color(pixel_t pixel, uint8_t* rgb)
{
    uint32_t rgbx;
    switch(pixel)
    {
#define M(p, value) case PIXEL_##p: rgbx = value; break
    M(NONE, 0x00000000); // #000000
    M(WIRE, 0xc2c3c700); // #c2c3c7
    M(IN,   0x00875100); // #008751
    M(OUT,  0xff004d00); // #ff004d
    M(OR,   0xab523600); // #ab5236
    M(AND,  0xffccaa00); // #ffccaa
    M(NOT,  0x83769c00); // #83769c
#undef M
    }

    rgb[0] = (rgbx & 0xff000000) >> 24;
    rgb[1] = (rgbx & 0x00ff0000) >> 16;
    rgb[2] = (rgbx & 0x0000ff00) >>  8;
}
