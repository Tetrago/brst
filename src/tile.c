#include "tile.h"

/**
 * \brief          Hashes a coordinate into a value used by the tile_store
 * \param[in]      x: Signed x coordinate
 * \param[in]      y: Signed y coordinate
 * \return         Hashed coordinate
 */
inline hash_map_key_t hash_xy(tile_coord_t x, tile_coord_t y)
{
    return ((uint64_t)x << 32) | y;
}

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
    return hash_map_insert(store->tile_map, hash_xy(x, y));
}

struct tile* tile_store_get(struct tile_store* store, tile_coord_t x, tile_coord_t y)
{
    return hash_map_get(store->tile_map, hash_xy(x, y));
}
