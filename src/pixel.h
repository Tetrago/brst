#ifndef BRST_PIXEL_H
#define BRST_PIXEL_H

#include <stdint.h>

#define PIXEL_NONE 0x00
#define PIXEL_WIRE 0x01
#define PIXEL_IN   0x02
#define PIXEL_OUT  0x03
#define PIXEL_OR   0x04
#define PIXEL_AND  0x05
#define PIXEL_NOT  0x06

typedef uint8_t   pixel_t;

/**
 * \brief          Colors in an RGB value with a pixel's color
 * \param[in]      pixel: Pixel to retrieve color of
 * \param[inout]   rgb: RGB array to modify
 */
void pixel_color(pixel_t pixel, uint8_t* rgb);

#endif
