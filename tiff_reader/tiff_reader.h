//
// Created by me on 16.10.23.
//

#ifndef TIFF_READER_TIFF_READER_H
#define TIFF_READER_TIFF_READER_H

#include <format>
#include <cstdint>
#include <span>
#include <fstream>
#include <iostream>
#include <vector>
#include "tag_types.h"
#include "contracts.h"
#include "tiff_reader.h"

namespace tiff_reader {

    /****
     * Types
     */
    struct TiffHeader {
        std::uint16_t byte_order;
        std::uint16_t tiff_id;
        std::int32_t ifd_offset;
    };

    struct IfdEntry {
        std::uint16_t tag;
        std::uint16_t field_type;
        std::uint32_t count;
        std::uint32_t value_or_offset;
    };

    /***
     * Constants
     */

    const unsigned short TIFF_ID = 42;
    constexpr int IfdEntrySize = sizeof(IfdEntry);

    /***
     * Methods
     */

    ImageDescription read_tiff_file(const std::string& file_path);
    void print_image_description(ImageDescription* desc);

    ImageDescription analyse_tiff_data(char* raw_data, long data_length);
}

#endif //TIFF_READER_TIFF_READER_H
