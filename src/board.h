#ifndef BRST_BLUEPRINT_H
#define BRST_BLUEPRINT_H

#include <stdint.h>

#include "pixel.h"
#include "tile.h"

/**
 * \brief          Pixel coordinate
 */
typedef int64_t coord_t;

/**
 * \brief          Board of pixels
 */
struct board
{
    struct tile_store* store;
};

/**
 * \brief          Creates a new empty board
 */
struct board* board_create();

/**
 * \brief          Destroys a board
 * \param[in]      board: board structure to destroy
 */
void board_destroy(struct board* board);

/**
 * \brief          Sets a pixel on the board
 * \param[in]      board: board structure to modify
 * \param[in]      x: X coordinate of pixel
 * \param[in]      y: Y coordinate of pixel
 * \param[in]      pixel: Pixel value to set coordinate to
 */
void board_set_pixel(struct board* board, coord_t x, coord_t y, pixel_t pixel);

#endif
