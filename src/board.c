#include "board.h"

#include <stdlib.h>

struct board* board_create()
{
    struct board* board = malloc(sizeof(struct board));
    board->store = tile_store_create();

    return board;
}

void board_destroy(struct board* board)
{
    tile_store_destroy(board->store);
    free(board);
}

void board_set_pixel(struct board* board, coord_t x, coord_t y, pixel_t pixel)
{
    struct tile* tile = tile_store_get_or_create(board->store, x / TILE_SIZE, y / TILE_SIZE);
    tile->pixels[(labs(y) % TILE_SIZE) * TILE_SIZE + (labs(x) % TILE_SIZE)] = pixel;
}
