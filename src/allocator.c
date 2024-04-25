#include "allocator.h"

#include <stdint.h>

struct allocator_block
{
    size_t size;                               /** Total size of used memory in block */
    size_t capacity;                           /** Total size of block */
    uint8_t* block;                            /** Block of memory belonging to this instance */
    struct allocator_block* next;              /** Next block of memory or NULL */
};

struct allocator* allocator_create(size_t block_size)
{
    struct allocator_block* block = malloc(sizeof(struct allocator_block));
    block->size = 0;
    block->capacity = block_size;
    block->block = malloc(block_size);
    block->next = NULL;

    struct allocator* allocator = malloc(sizeof(struct allocator));
    allocator->block_size = block_size;
    allocator->block = block;

    return allocator;
}

void* allocator_new(struct allocator* allocator, size_t size)
{
    struct allocator_block* block = allocator->block;
    while(block->capacity - block->size < size)
    {
        if(block->next)
        {
            block = block->next;
            continue;
        }

        struct allocator_block* next = malloc(sizeof(struct allocator_block));
        next->size = size;
        next->capacity = size < allocator->block_size ? allocator->block_size : size;
        next->block = malloc(next->capacity);
        next->next = NULL;

        block->next = next;
        return next->block;
    }

    void* ret = block->block + block->size;
    block->size += size;
    return ret;
}

void allocator_destroy(struct allocator* allocator)
{
    struct allocator_block* block = allocator->block;
    while(block)
    {
        free(block->block);
        block = block->next;
    }

    free(allocator);
}
