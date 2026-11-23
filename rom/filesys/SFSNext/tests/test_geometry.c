/* Host-side phase 1 arithmetic tests; does not mount or write disks. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "../include/sfsnext_io.h"
int main(void) {
    uint64_t offset = 0;
    assert(sfsnext_valid_block_size(512));
    assert(sfsnext_valid_block_size(4096));
    assert(sfsnext_valid_block_size(32768));
    assert(!sfsnext_valid_block_size(0));
    assert(!sfsnext_valid_block_size(1000));
    assert(!sfsnext_valid_block_size(65536));
    assert(sfsnext_block_offset(0, 4096, &offset) && offset == 0);
    assert(sfsnext_block_offset(UINT64_C(1) << 32, 4096, &offset)
           && offset == (UINT64_C(1) << 44));
    assert(!sfsnext_block_offset(UINT64_MAX, 4096, &offset));
    assert(!sfsnext_block_offset(1, 4096, NULL));
    assert(sfsnext_partition_offset(512, 2, 4096, &offset)
           && offset == 8704);
    assert(!sfsnext_partition_offset(UINT64_MAX, 1, 512, &offset));
    assert(sfsnext_extent_bounds(9, 1, 10));
    assert(!sfsnext_extent_bounds(9, 2, 10));
    assert(!sfsnext_extent_bounds(0, 0, 10));
    assert(!sfsnext_extent_bounds(UINT64_MAX, 2, UINT64_MAX));
    puts("SFS Next phase 1 geometry tests passed");
    return 0;
}
