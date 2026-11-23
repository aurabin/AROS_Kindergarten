/* Phase 1 read-only fixed-endian SFNX header parser. No disk writes. */
#ifndef SFSNEXT_CODEC_H
#define SFSNEXT_CODEC_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sfsnext_disk.h"
#include "sfsnext_io.h"
#include "sfsnext_checksum.h"
static inline uint16_t sfsnext_be16(const uint8_t *p) {
    return (uint16_t)(((uint16_t)p[0] << 8) | p[1]);
}
static inline uint32_t sfsnext_be32(const uint8_t *p) {
    return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
           ((uint32_t)p[2] << 8) | p[3];
}
static inline uint64_t sfsnext_be64(const uint8_t *p) {
    return ((uint64_t)sfsnext_be32(p) << 32) | sfsnext_be32(p + 4);
}
/* Validates draft header structure and CRC64. Not a mount authorization. */
static inline bool sfsnext_parse_header_draft(const uint8_t *data, size_t len,
                                                sfsnext_root_fields *out) {
    if (!data || !out || len < SFSNEXT_HEADER_BYTES ||
        sfsnext_be32(data) != SFSNEXT_MAGIC ||
        sfsnext_be16(data + 4) != SFSNEXT_VERSION ||
        sfsnext_be16(data + 6) != SFSNEXT_HEADER_BYTES) return false;
    for (size_t i = 72; i < 80; ++i) if (data[i] != 0) return false;
    sfsnext_root_fields r;
    r.generation = sfsnext_be64(data + 8);
    r.total_blocks = sfsnext_be64(data + 16);
    r.root_tree_block = sfsnext_be64(data + 24);
    r.free_space_root = sfsnext_be64(data + 32);
    r.journal_start = sfsnext_be64(data + 40);
    r.journal_blocks = sfsnext_be64(data + 48);
    r.block_size = sfsnext_be32(data + 56);
    r.feature_flags = sfsnext_be32(data + 60);
    r.checksum = sfsnext_be64(data + 64);
    if (!sfsnext_valid_block_size(r.block_size) ||
        r.total_blocks < 3 || r.feature_flags != 0 ||
        r.root_tree_block == 0 || r.free_space_root == 0 ||
        r.root_tree_block == r.free_space_root ||
        r.root_tree_block >= r.total_blocks ||
        r.free_space_root >= r.total_blocks ||
        r.total_blocks > UINT64_MAX / r.block_size ||
        (r.journal_blocks && !sfsnext_extent_bounds(
             r.journal_start, r.journal_blocks, r.total_blocks))) return false;
    if (r.journal_blocks &&
        ((r.root_tree_block >= r.journal_start &&
          r.root_tree_block - r.journal_start < r.journal_blocks) ||
         (r.free_space_root >= r.journal_start &&
          r.free_space_root - r.journal_start < r.journal_blocks))) return false;
    if (r.checksum != sfsnext_crc64_header(data)) return false;
    *out = r;
    return true;
}
#endif
