#include "hash_map.h"

#include <string.h>

#define ADDR_VALUE(entry) (void*)(((uint8_t*)(entry)) + sizeof(struct hash_map_entry))

struct hash_map_entry
{
    hash_map_key_t key;                        /** Key of this element */
    struct hash_map_entry* next;               /** Next entry or NULL. When NULL, this entry stores no value */
};

struct hash_map* hash_map_create(size_t element_size)
{
    struct hash_map* hash_map = malloc(sizeof(struct hash_map));
    hash_map->stride = sizeof(struct hash_map_entry) + element_size;
    hash_map->capacity = 256;
    hash_map->size = 0;
    hash_map->allocator = allocator_create(hash_map->stride * hash_map->capacity);
    hash_map->map = allocator_new(hash_map->allocator, hash_map->stride * hash_map->capacity);

    memset(hash_map->map, 0, hash_map->stride * hash_map->capacity);
    return hash_map;
}

void hash_map_destroy(struct hash_map* hash_map)
{
    allocator_destroy(hash_map->allocator);
    free(hash_map);
}

static struct hash_map_entry* traverse(struct hash_map* hash_map, hash_map_key_t key)
{
    struct hash_map_entry* entry = (struct hash_map_entry*)&hash_map->map[hash_map->stride * (key % hash_map->capacity)];

    // While there is a new entry
    while(entry->key != key && entry->next)
    {
        entry = entry->next;
    }

    return entry;
}

void* hash_map_get(struct hash_map* hash_map, hash_map_key_t key)
{
    struct hash_map_entry* entry = traverse(hash_map, key);
    if(!entry->next)
    {
        return NULL;
    }

    return ADDR_VALUE(entry);
}

void* hash_map_insert(struct hash_map* hash_map, hash_map_key_t key)
{
    struct hash_map_entry* entry = traverse(hash_map, key);

    // If the found entry was set, return it
    if(entry->next)
    {
        return ADDR_VALUE(entry);
    }

    ++hash_map->size;

    // Create and zero a new end entry
    struct hash_map_entry* next = allocator_new(hash_map->allocator, hash_map->stride);
    memset(next, 0, hash_map->stride);

    entry->key = key;
    entry->next = next;

    return ADDR_VALUE(entry);
}

void hash_map_iter(struct hash_map* hash_map, struct hash_map_iterator* iterator)
{
    iterator->hash_map = hash_map;
    iterator->index = 0;
    iterator->entry = (struct hash_map_entry*)iterator->hash_map->map;
}

void* hash_map_next(struct hash_map_iterator* iterator)
{
    // While the current entry is invalid
    while(!iterator->entry->next)
    {
        // Move to the next linked list
        if(++iterator->index == iterator->hash_map->capacity)
        {
            // If we've moved past the last linked list, there are no more items
            return NULL;
        }

        // Move to the next linked list
        iterator->entry = (struct hash_map_entry*)&iterator->hash_map->map[iterator->index * iterator->hash_map->stride];
    }

    void* ret = ADDR_VALUE(iterator->entry);
    iterator->entry = iterator->entry->next;
    return ret;
}
