#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../include/sfsnext_codec.h"
int main(void) {
    uint8_t b[SFSNEXT_HEADER_BYTES] = {0};
    sfsnext_root_fields root;
    b[0]='S'; b[1]='F'; b[2]='N'; b[3]='X';
    b[5]=1; b[7]=SFSNEXT_HEADER_BYTES;
    b[23]=16; /* total_blocks = 16 */
    b[31]=1; /* root_tree_block = 1 */
    b[39]=2; /* free_space_root = 2 */
    b[54]=0x10; /* block_size = 4096 (offset 56, corrected below) */
    b[54]=0; b[57]=0x10;
    assert(sfsnext_parse_header_draft(b, sizeof b, &root));
    assert(root.total_blocks==16 && root.block_size==4096);
    b[0]='X'; assert(!sfsnext_parse_header_draft(b,sizeof b,&root)); b[0]='S';
    b[79]=1; assert(!sfsnext_parse_header_draft(b,sizeof b,&root)); b[79]=0;
    b[63]=1; assert(!sfsnext_parse_header_draft(b,sizeof b,&root)); b[63]=0;
    assert(!sfsnext_parse_header_draft(b, 79, &root));
    assert(!sfsnext_parse_header_draft(NULL,80,&root));
    puts("SFS Next draft codec tests passed");
    return 0;
}
