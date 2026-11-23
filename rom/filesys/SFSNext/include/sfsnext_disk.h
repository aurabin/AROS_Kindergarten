/* SFS Next experimental on-disk format v1. Not legacy SFS compatible.
 * This header defines logical fields; never fwrite() C structs to disk.
 * SPDX-License-Identifier: MIT
 */
#ifndef SFSNEXT_DISK_H
#define SFSNEXT_DISK_H
#include <stdint.h>
#include <stddef.h>
#define SFSNEXT_MAGIC UINT32_C(0x53464E58) /* SFNX */
#define SFSNEXT_VERSION UINT16_C(1)
#define SFSNEXT_HEADER_BYTES 80u
#define SFSNEXT_MIN_BLOCK_BYTES 512u
#define SFSNEXT_MAX_BLOCK_BYTES 32768u
typedef uint64_t sfsnext_block_t;
typedef struct {
    uint64_t generation, total_blocks, root_tree_block;
    uint64_t free_space_root, journal_start, journal_blocks;
    uint32_t block_size, feature_flags;
    uint64_t checksum;
} sfsnext_root_fields;
/* Explicit big-endian offsets, independent of compiler padding:
 * 0 magic:u32; 4 version:u16; 6 header_bytes:u16;
 * 8 generation:u64; 16 total_blocks:u64; 24 root_tree_block:u64;
 * 32 free_space_root:u64; 40 journal_start:u64; 48 journal_blocks:u64;
 * 56 block_size:u32; 60 feature_flags:u32; 64 checksum:u64;
 * 72..79 reserved, must be zero.
 * Checksum algorithm and commit protocol are NOT specified in phase 1.
 * Consequently no production formatter or writable mount is permitted.
 */
#endif
