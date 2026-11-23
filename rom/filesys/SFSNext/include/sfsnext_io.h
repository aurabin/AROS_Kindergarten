/* Overflow-checked arithmetic for experimental 64-bit SFS Next.
 * SPDX-License-Identifier: MIT
 */
#ifndef SFSNEXT_IO_H
#define SFSNEXT_IO_H
#include <stdint.h>
#include <stdbool.h>
#include "sfsnext_disk.h"
static inline bool sfsnext_valid_block_size(uint32_t size) {
    return size >= SFSNEXT_MIN_BLOCK_BYTES &&
           size <= SFSNEXT_MAX_BLOCK_BYTES && (size & (size - 1u)) == 0;
}
static inline bool sfsnext_block_offset(uint64_t block, uint32_t size,
                                         uint64_t *out) {
    if (!out || !sfsnext_valid_block_size(size) ||
        block > UINT64_MAX / size) return false;
    *out = block * (uint64_t)size;
    return true;
}
static inline bool sfsnext_extent_bounds(uint64_t first, uint64_t count,
                                          uint64_t total) {
    return count != 0 && first < total && count <= total - first;
}
static inline bool sfsnext_partition_offset(uint64_t base, uint64_t block,
                                              uint32_t size, uint64_t *out) {
    uint64_t relative;
    if (!out || !sfsnext_block_offset(block, size, &relative) ||
        base > UINT64_MAX - relative) return false;
    *out = base + relative;
    return true;
}
#endif
