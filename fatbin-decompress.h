/** Decompress nvcc fatbin files
 *
 * Author: Niklas Eiling <niklas.eiling@rwth-aachen.de>
 * SPDX-FileCopyrightText: 2023 Niklas Eiling <niklas.eiling@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 *********************************************************************************/

#ifndef __FATBIN_DECOMPRESS_H__
#define __FATBIN_DECOMPRESS_H__

#include <stdint.h>

__pragma( pack( push, 1 ) )
struct fat_elf_header
{
    uint32_t magic;
    uint16_t version;
    uint16_t header_size;
    uint64_t size;
};
struct fat_text_header
{
    uint16_t kind;
    uint16_t unknown1;
    uint32_t header_size;
    uint64_t size;
    uint32_t compressed_size;       // Size of compressed data
    uint32_t unknown2;              // Address size for PTX?
    uint16_t minor;
    uint16_t major;
    uint32_t arch;
    uint32_t obj_name_offset;
    uint32_t obj_name_len;
    uint64_t flags;
    uint64_t zero;                  // Alignment for compression?
    uint64_t decompressed_size;     // Length of compressed data in decompressed representation.
                                    // There is an uncompressed footer so this is generally smaller
                                    // than size.
};
__pragma( pack( pop ) )

size_t decompress(const uint8_t* input, size_t input_size, uint8_t* output, size_t output_size);
size_t decompress_fatbin(const uint8_t* fatbin_data, size_t fatbin_size, uint8_t** decompressed_data);

#endif // __FATBIN_DECOMPRESS_H__