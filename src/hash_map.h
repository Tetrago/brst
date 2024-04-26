#ifndef BRST_HASH_MAP_H
#define BRST_HASH_MAP_H

#include <stdint.h>

#include "allocator.h"

/**
 * \brief          Hash type used by hash maps
 */
typedef uint64_t hash_map_key_t;

/**
 * \brief          Structure immediately preceding all map values
 */
struct hash_map_entry;

/**
 * Hash map structure
 */
struct hash_map
{
    size_t stride;                             /** Byte size of each value element combined with the size of a hash_map_entry */
    size_t capacity;                           /** The number of unique hash entries available */
    size_t size;                               /** The total number of pairs in the hash map */
    struct allocator* allocator;               /** Allocator used to store entries */
    uint8_t* map;                              /** Array of linked list entries, with a trailing empty entry. Each element of the
                                                  array consists of a hash_map_entry immediately followed by the element */
};

/**
 * \brief          Iterator structure used to iterate through each item in a hash map
 */
struct hash_map_iterator
{
    struct hash_map* hash_map;                 /** hash_map structure that this iterator belongs to */
    size_t index;                              /** Index into linked list map that the iterator is currently on */
    struct hash_map_entry* entry;              /** Next entry in iteration */
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

/**
 * \brief          Constructs a new iterator for a hash map
 * \param[in]      hash_map: Hash map to iterate through
 * \param[out]     iterator: hash_map_iterator structure to initialize
 */
void hash_map_iter(struct hash_map* hash_map, struct hash_map_iterator* iterator);

/**
 * \brief          Retrieves the next item from an iterator
 * \param[inout]   iterator: Iterator to advance
 * \return         Next item or NULL
 */
void* hash_map_next(struct hash_map_iterator* iterator);

#endif
