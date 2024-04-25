#include "tile.h"

#include <string.h>

#include "allocator.h"

/**
 * \brief          Hash of x and y coordinates
 */
typedef uint64_t hash_t;

/**
 * \brief          Hashes a coordinate into a value used by the tile_store
 * \param[in]      x: Signed x coordinate
 * \param[in]      y: Signed y coordinate
 * \return         Hashed coordinate
 */
inline hash_t hash_xy(tile_coord_t x, tile_coord_t y)
{
    return ((uint64_t)x << 32) | y;
}

/**
 * \brief          Linked hash map entry
 */
struct tile_store_entry
{
    hash_t hash;                               /** The hash value of this entry */
    struct tile* tile;                         /** The tile stored at this hash value */
    struct tile_store_entry* next;             /** Next entry in linked list or NULL if none */
};

/**
 * \brief          Tile store iterator
 */
struct tile_store_iterator
{
    struct tile_store* store;
    hash_t index;
    struct tile_store_entry* current;
};

struct tile_store* tile_store_create()
{
    struct tile_store* store = malloc(sizeof(struct tile_store));
    store->size = 0;
    store->capacity = 64;
    store->allocator = allocator_create(sizeof(struct tile_store_entry) * store->capacity);
    store->map = allocator_new(store->allocator, sizeof(struct tile_store_entry) * store->capacity);

    memset(store->map, 0, sizeof(struct tile_store_entry) * store->capacity);

    return store;
}

void tile_store_destroy(struct tile_store* store)
{
    allocator_destroy(store->allocator);
    free(store);
}

struct tile* tile_store_get_or_create(struct tile_store* store, tile_coord_t x, tile_coord_t y)
{
    hash_t hash = hash_xy(x, y);
    struct tile_store_entry* entry = &store->map[hash % store->capacity];

    while(hash != entry->hash && entry->tile)
    {
        entry = entry->next;
    }

    if(entry->tile)
    {
        return entry->tile;
    }

    struct tile_store_entry* next = allocator_new(store->allocator, sizeof(struct tile_store_entry));
    next->tile = NULL;
    next->next = NULL;

    entry->hash = hash;
    entry->tile = malloc(sizeof(struct tile));
    entry->next = next;

    memset(entry->tile->pixels, PIXEL_NONE, sizeof(pixel_t) * TILE_SIZE * TILE_SIZE);

    ++store->size;
    return entry->tile;
}

struct tile* tile_store_get(struct tile_store* store, tile_coord_t x, tile_coord_t y)
{
    hash_t hash = hash_xy(x, y);
    struct tile_store_entry* entry = &store->map[hash % store->capacity];

    while(hash != entry->hash && entry->tile)
    {
        entry = entry->next;
    }

    if(entry->tile)
    {
        return entry->tile;
    }
    else
    {
        return NULL;
    }
}

void tile_store_iter(struct tile_store* store, struct tile_store_iterator* iterator)
{
    iterator->store = store;
    iterator->index = 0;
    iterator->current = &store->map[0];
}

struct tile* tile_store_next(struct tile_store_iterator* iterator)
{
    // Loop to find next filled entry
    while(!iterator->current->tile)
    {
        // If we've hit the last one, stop iterating
        if(iterator->index++ == iterator->store->capacity)
        {
            return NULL;
        }
    }

    struct tile* ret = iterator->current->tile;
    iterator->current = iterator->current->next;

    return ret;
}
