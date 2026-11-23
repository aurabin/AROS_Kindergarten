# SFNX v1 disk format – NON-NORMATIVE DRAFT

**Status:** design-only. No formatter, writer or mount implementation is authorized by this document.

All integer fields are unsigned and **big endian**. The 80-byte proposed header starts at byte zero of a standalone SFNX image (partition-relative); no bootblock or reserved-block scheme has yet been decided.

| Offset | Width | Field |
| ---: | ---: | --- |
| 0 | 4 | magic = 0x53464E58 (SFNX) |
| 4 | 2 | version = 1 |
| 6 | 2 | header length = 80 |
| 8 | 8 | generation |
| 16 | 8 | total blocks |
| 24 | 8 | root tree block |
| 32 | 8 | free space root |
| 40 | 8 | journal start |
| 48 | 8 | journal length in blocks |
| 56 | 4 | block size (512..32768, power of two) |
| 60 | 4 | feature flags (must be zero in phase 1) |
| 64 | 8 | CRC64-ECMA-182 of 80-byte header with bytes 64..71 zeroed |
| 72 | 8 | reserved (must be zero) |

## Design decisions still required before writes
1. Choose and test a checksumming algorithm, coverage, checksum-field-zeroing, and failure behavior.
2. Specify two or more redundant superblocks and a torn-write recovery policy.
3. Define generation and flush ordering with device write barriers.
4. Define 64-bit object IDs, extent trees, free-space allocation and endian encoders.
5. Define explicit incompatibility/compatibility feature bits and upgrade rules.
6. Require exact partition size and bounds checks and ensure all I/O stays within it.
7. Specify 64-bit AROS DOS API integration; legacy Seek() signatures must not silently truncate.
8. Verify licensing and portability across supported AROS targets.

**Security:** structural parsing alone is NOT sufficient to mount, repair or write an SFNX image. No legacy SFS image is converted in place.
