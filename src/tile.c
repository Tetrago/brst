#include "tile.h"

#include <string.h>

struct tile_store* tile_store_create()
{
    struct tile_store* store = malloc(sizeof(struct tile_store));
    store->tile_map = hash_map_create(sizeof(struct tile));

    return store;
}

void tile_store_destroy(struct tile_store* store)
{
    hash_map_destroy(store->tile_map);
    free(store);
}

struct tile* tile_store_get_or_create(struct tile_store* store, tile_coord_t x, tile_coord_t y)
{
    struct tile* tile = hash_map_get(store->tile_map, hash_xy(x, y));
    if(tile)
    {
        return tile;
    }

    tile = hash_map_insert(store->tile_map, hash_xy(x, y));
    tile->x = x;
    tile->y = y;
    memset(tile->pixels, PIXEL_NONE, sizeof(pixel_t) * TILE_SIZE * TILE_SIZE);

    return tile;
}

struct tile* tile_store_get(struct tile_store* store, tile_coord_t x, tile_coord_t y)
{
    return hash_map_get(store->tile_map, hash_xy(x, y));
}
