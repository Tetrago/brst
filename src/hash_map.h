#ifndef BRST_HASH_MAP_H
#define BRST_HASH_MAP_H

#include <stdint.h>

#include "allocator.h"

/**
 * \brief          Hash type used by hash maps
 */
typedef uint64_t hash_map_key_t;

/**
 * Hash map structure
 */
struct hash_map
{
    size_t stride;                             /** Byte size of each element combined with the size of hash_map_key_t and a
                                                  pointer to the next entry, as described in the map variable */
    size_t capacity;                           /** The number of unique hash entries available */
    size_t size;                               /** The total number of pairs in the hash map */
    struct allocator* allocator;               /** Allocator used to store entries */
    uint8_t* map;                              /** Array of linked list entries, with a trailing empty entry. Each element of the
                                                  array consists of a hash_map_key_t, the element itself, and a pointer to the next
                                                  array element, all tightly packed together */
};

/**
 * \brief          Creates a hash map
 * \param[in]      element_size: The size of each value that corresponds to a key
 * \return         Initialized hash map
 */
struct hash_map* hash_map_create(size_t element_size);

/**
 * \brief          Destroys the hash map and all associated memory
 * \param[in]      hash_map: Hash map to deconstruct
 */
void hash_map_destroy(struct hash_map* hash_map);

/**
 * \brief          Gets the element associated to the given key
 * \param[in]      hash_map: Hash map structure to search through
 * \param[in]      key: Key of requested value
 * \return         Value associated with the given key or NULL
 */
void* hash_map_get(struct hash_map* hash_map, hash_map_key_t key);

/**
 * \brief          Inserts an item
 * \param[in]      hash_map: Hash map structure
 * \param[in]      key: Key to insert
 * \return         New value or NULL if key already exists
 */
void* hash_map_insert(struct hash_map* hash_map, hash_map_key_t key);

#endif
