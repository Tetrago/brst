#ifndef BRST_ALLOCATOR_H
#define BRST_ALLOCATOR_H

#include <stdlib.h>

struct allocator_block;

/**
 * \brief          Block-based contiguous memory allocator
 */
struct allocator
{
    size_t block_size;                         /** Number of elements per block */
    struct allocator_block* block;             /** First block of memory, used for destruction */
};

/**
 * \brief          Creates a new contiguous block allocator
 * \param[in]      block_size: Minimum size of memory that each block should contain
 * \return         Initialized allocator
 */
struct allocator* allocator_create(size_t block_size);

/**
 * \brief          Allocates new memory
 * \param[in]      allocator: Allocator to pull from
 * \param[in]      size: Size of segment to allocate
 * \return         Allocated element owned by the allocator, do not individually free this address
 */
void* allocator_new(struct allocator* allocator, size_t size);

/**
 * \brief          Deconstructs the allocator and frees all memory
 * \param[in]      allocator: Allocator to destroy
 */
void allocator_destroy(struct allocator* allocator);

#endif
