/* CRC64-ECMA-182 for SFNX v1 header draft.
 * Polynomial 0x42F0E1EBA9EA3693, init=0, xorout=0, no reflection.
 * Checksum field bytes 64..71 are treated as zero. */
#ifndef SFSNEXT_CHECKSUM_H
#define SFSNEXT_CHECKSUM_H
#include <stdint.h>
#include <stddef.h>
#include "sfsnext_disk.h"
static inline uint64_t sfsnext_crc64_header(const uint8_t *header) {
    uint64_t crc = UINT64_C(0);
    for (size_t i = 0; i < SFSNEXT_HEADER_BYTES; ++i) {
        uint8_t value = (i >= 64 && i < 72) ? 0 : header[i];
        crc ^= (uint64_t)value << 56;
        for (unsigned bit = 0; bit < 8; ++bit)
            crc = (crc & UINT64_C(0x8000000000000000))
                ? (crc << 1) ^ UINT64_C(0x42F0E1EBA9EA3693)
                : (crc << 1);
    }
    return crc;
}
#endif
