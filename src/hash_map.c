#include "hash_map.h"

#include <string.h>

#define ENTRY_KEY(entry) ((hash_map_key_t*)(entry))
#define ENTRY_VALUE(entry) ((uint8_t*)(entry) + sizeof(hash_map_key_t))
#define ENTRY_NEXT(entry, stride) (void**)((uint8_t*)(entry) + (stride) - sizeof(void*))

struct hash_map* hash_map_create(size_t element_size)
{
    struct hash_map* hash_map = malloc(sizeof(struct hash_map));
    hash_map->stride = element_size + sizeof(hash_map_key_t) + sizeof(void*);
    hash_map->capacity = 256;
    hash_map->size = 0;
    hash_map->allocator = allocator_create(hash_map->stride * hash_map->capacity);
    hash_map->map = allocator_new(hash_map->allocator, hash_map->capacity);

    memset(hash_map->map, 0, hash_map->stride * hash_map->capacity);
    return hash_map;
}

void hash_map_destroy(struct hash_map* hash_map)
{
    allocator_destroy(hash_map->allocator);
    free(hash_map);
}

static void* traverse(struct hash_map* hash_map, hash_map_key_t key)
{
    void* entry = &hash_map->map[hash_map->stride * (key % hash_map->capacity)];

    // While there is a new entry
    while(*ENTRY_KEY(entry) != key && ENTRY_NEXT(entry, hash_map->stride))
    {
        entry = *ENTRY_NEXT(entry, hash_map->stride);
    }

    return entry;
}

void* hash_map_get(struct hash_map* hash_map, hash_map_key_t key)
{
    return traverse(hash_map, key) + sizeof(hash_map_key_t);
}

void* hash_map_insert(struct hash_map* hash_map, hash_map_key_t key)
{
    void* entry = traverse(hash_map, key);

    // If the found entry was set, return it
    if(ENTRY_NEXT(entry, hash_map->stride))
    {
        return ENTRY_VALUE(entry);
    }

    // Create and zero a new end entry
    void* next = allocator_new(hash_map->allocator, hash_map->stride);
    memset(next, 0, hash_map->stride);

    // Update entry with new end
    *ENTRY_NEXT(entry, hash_map->stride) = next;

    // Update entry with key
    *ENTRY_KEY(entry) = key;

    // Return new value
    return ENTRY_VALUE(entry);
}
