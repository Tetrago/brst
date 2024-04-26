#include "view.h"

#include <stdlib.h>

struct entry
{
    struct tile* tile;
    struct SDL_Texture* texture;
};

struct view* view_create(struct board* board, SDL_Renderer* renderer)
{
    struct view* view = malloc(sizeof(struct view));
    view->board = board;
    view->renderer = renderer;
    view->texture_map = hash_map_create(sizeof(struct entry));

    return view;
}

void view_destroy(struct view* view)
{
    struct hash_map_iterator iter;
    hash_map_iter(view->texture_map, &iter);

    struct entry* entry;
    while((entry = hash_map_next(&iter)))
    {
        SDL_DestroyTexture(entry->texture);
    }

    hash_map_destroy(view->texture_map);
    free(view);
}

void view_redraw(struct view* view)
{
    struct hash_map_iterator iter;
    hash_map_iter(view->board->store->tile_map, &iter);

    struct tile* tile;
    while((tile = hash_map_next(&iter)))
    {
        struct entry* entry = hash_map_get(view->texture_map, hash_xy(tile->x, tile->y));
        if(!entry)
        {
            entry = hash_map_insert(view->texture_map, hash_xy(tile->x, tile->y));
            entry->tile = tile;
            entry->texture = SDL_CreateTexture(view->renderer,
                                               SDL_PIXELFORMAT_RGB24,
                                               SDL_TEXTUREACCESS_STREAMING,
                                               TILE_SIZE,
                                               TILE_SIZE);
        }

        uint8_t* pixels;
        int pitch;
        SDL_LockTexture(entry->texture, NULL, (void**)&pixels, &pitch);
        int stride = pitch / TILE_SIZE;

        for(int x = 0; x < TILE_SIZE; ++x)
        {
            for(int y = 0; y < TILE_SIZE; ++y)
            {
                pixel_color(tile->pixels[y * TILE_SIZE + x], &pixels[y * pitch + x * stride]);
            }
        }

        SDL_UnlockTexture(entry->texture);
    }
}

void view_render(struct view* view)
{
    struct hash_map_iterator iter;
    hash_map_iter(view->texture_map, &iter);

    struct entry* entry;
    while((entry = hash_map_next(&iter)))
    {
        SDL_Rect rect;
        rect.x = entry->tile->x * TILE_SIZE;
        rect.y = entry->tile->y * TILE_SIZE;
        rect.w = TILE_SIZE;
        rect.h = TILE_SIZE;

        SDL_RenderCopy(view->renderer, entry->texture, NULL, &rect);
    }
}
