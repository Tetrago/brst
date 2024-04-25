#include "view.h"
#include "pixel.h"
#include "tile.h"

#include <stdlib.h>

struct view* view_create(struct board* board, SDL_Renderer* renderer, int width, int height)
{
    struct view* view = malloc(sizeof(struct view));
    view->board = board;
    view->renderer = renderer;
    view->texture = NULL;

    view_resize(view, width, height);

    return view;
}

void view_destroy(struct view* view)
{
    if(view->texture)
    {
        SDL_DestroyTexture(view->texture);
    }

    free(view);
}

void view_resize(struct view* view, int width, int height)
{
    if(view->texture)
    {
        SDL_DestroyTexture(view->texture);
    }

    view->texture = SDL_CreateTexture(view->renderer,
                                      SDL_PIXELFORMAT_RGB24,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      width,
                                      height);
    view->width = width;
    view->height = height;
}

void view_redraw(struct view* view, coord_t x, coord_t y)
{
    int tiles_per_width = (view->width + TILE_SIZE - 1) / TILE_SIZE;
    int tiles_per_height = (view->height + TILE_SIZE - 1) / TILE_SIZE;

    // Position of first tile clipped by view
    int tile_x_origin = x - (x % TILE_SIZE);
    int tile_y_origin = y - (y % TILE_SIZE);

    struct tile* tiles[tiles_per_width * tiles_per_height];

    for(int tx = 0; tx < tiles_per_width; ++tx)
    {
        for(int ty = 0; ty < tiles_per_height; ++ty)
        {
            tiles[ty * tiles_per_width + tx] = tile_store_get(view->board->store,
                                                              tile_x_origin + tx * TILE_SIZE,
                                                              tile_y_origin + ty * TILE_SIZE);
        }
    }

    // Screen-space offset to origin tile
    int x_offset = -(x % TILE_SIZE);
    int y_offset = -(y % TILE_SIZE);

    int pitch;
    uint8_t* pixels;
    SDL_LockTexture(view->texture, NULL, (void**)&pixels, &pitch);
    memset(pixels, 0, pitch * view->height);

    int stride = pitch / view->width;

    for(int tile_x = 0; tile_x < tiles_per_width; ++tile_x)
    {
        for(int tile_y = 0; tile_y < tiles_per_height; ++tile_y)
        {
            struct tile* tile = tiles[tile_y * tiles_per_width + tile_x];
            if(!tile) continue;

            for(int pixel_x = 0; pixel_x < TILE_SIZE; ++pixel_x)
            {
                for(int pixel_y = 0; pixel_y < TILE_SIZE; ++pixel_y)
                {
                    int texture_x = tile_x * TILE_SIZE + pixel_x - x_offset;
                    int texture_y = tile_y * TILE_SIZE + pixel_y - y_offset;
                    if(texture_x < 0 || texture_x >= view->width || texture_y < 0 || texture_y >= view->height) continue;

                    pixel_t pixel = tile->pixels[pixel_y * TILE_SIZE + pixel_x];
                    pixel_color(pixel, &pixels[texture_y * pitch + texture_x * stride]);
                }
            }
        }
    }

    SDL_UnlockTexture(view->texture);
}
