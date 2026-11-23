/* Read-only experimental SFNX header inspector. Never writes to input. */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "../include/sfsnext_codec.h"
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <disk-image>\n", argv[0]);
        return 2;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("open"); return 2; }
    uint8_t header[SFSNEXT_HEADER_BYTES];
    size_t got = fread(header, 1, sizeof header, f);
    int read_error = ferror(f);
    if (fclose(f) != 0 || read_error || got != sizeof header) {
        fprintf(stderr, "Cannot read complete SFNX header\n");
        return 2;
    }
    sfsnext_root_fields r;
    if (!sfsnext_parse_header_draft(header, sizeof header, &r)) {
        fprintf(stderr, "Not a structurally valid SFNX v1 draft header\n");
        return 1;
    }
    printf("SFNX v1 DRAFT (UNVERIFIED; NOT MOUNTABLE)\n");
    printf("generation: %" PRIu64 "\n", r.generation);
    printf("total blocks: %" PRIu64 "\n", r.total_blocks);
    printf("block bytes: %" PRIu32 "\n", r.block_size);
    printf("root tree block: %" PRIu64 "\n", r.root_tree_block);
    printf("free space root: %" PRIu64 "\n", r.free_space_root);
    printf("journal blocks: %" PRIu64 "\n", r.journal_blocks);
    puts("WARNING: checksum, file size and crash consistency not verified");
    return 0;
}
