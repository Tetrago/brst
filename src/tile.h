#ifndef BRST_TILE_H
#define BRST_TILE_H

#ifndef TILE_SIZE
#define TILE_SIZE 64
#endif

#include <stdint.h>

#include "hash_map.h"
#include "pixel.h"

/**
 * \brief          Value used to store tile coordinates
 */
typedef int32_t tile_coord_t;

/**
 * \brief          Node container
 */
struct tile
{
    pixel_t pixels[TILE_SIZE * TILE_SIZE];
};

/**
 * \brief          Hash map storing tiles at specified coordinates
 */
struct tile_store
{
    struct hash_map* tile_map;
};

/**
 * \brief          Creates a tile store
 * \return         Initialized tile store
 */
struct tile_store* tile_store_create();

/**
 * \brief          Deconstructs a tile store
 * \param[in]      store: tile_store structure to destroy
 */
void tile_store_destroy(struct tile_store* store);

/**
 * \brief          Retrieves a tile at a coordinate or creates a new one if it does not exist
 * \param[in]      store: tile_store to retreive from
 * \param[in]      x: X coordinate
 * \param[in]      y: Y coordinate
 * \return         tile at coordinate
 */
struct tile* tile_store_get_or_create(struct tile_store* store, tile_coord_t x, tile_coord_t y);

/**
 * \brief          Retrieves a tile at a coordinate
 * \param[in]      store: tile_store to retreive from
 * \param[in]      x: X coordinate
 * \param[in]      y: Y coordinate
 * \return         tile at coordinate or NULL
 */
struct tile* tile_store_get(struct tile_store* store, tile_coord_t x, tile_coord_t y);

#endif
