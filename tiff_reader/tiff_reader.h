//
// Created by me on 16.10.23.
//

#ifndef TIFF_READER_TIFF_READER_H
#define TIFF_READER_TIFF_READER_H

#include <iostream>
#include <fstream>
#include <array>
#include <format>
#include <vector>
#include <cstdint>
#include <cstring>
#include "tag_types.h"

using namespace std;

/****
 * Types
 */
struct TiffHeader {
    std::uint16_t byte_order;
    std::uint16_t tiff_id;
    std::int32_t ifd_offset;
};

struct IfdEntry {
    std::uint16_t field_type;
    std::uint32_t count;
    std::uint32_t value;
    std::uint16_t tag;
};

class ImageDescription {
public:
    ImageDescription(): width(0), height(0), compression_tag(0), color_shape_tag(0), bits_per_pixel_tag(0), sample_per_pixel(0) {};
    std::vector<uint8_t > pixel_bytes;
    std::uint16_t width;
    std::uint16_t height;
    std::uint16_t compression_tag;
    std::uint16_t color_shape_tag;
    std::uint16_t bits_per_pixel_tag;
    std::uint16_t sample_per_pixel;
};

/***
 * Constants
 */

const unsigned short TIFF_ID = 42;
constexpr int IfdEntrySize = sizeof(IfdEntry);

/***
 * Methods
 */

template<typename T>
auto slice(T &&container, int left, int right) {
    if (right > 9) {
        return std::span(begin(std::forward<T>(container)) + left, begin(std::forward<T>(container)) + right);
    }else {
        return std::span(begin(std::forward<T>(container)) + left, end(std::forward<T>(container)) + right);
    }
}

void describe_tiff(const ImageDescription* desc) {
    if(desc->color_shape_tag != RGB_COLOR_SPACE) {
        cout << "TIFF uses " << desc->color_shape_tag << ", this app supports only RBG" << std::endl;
        return;
    }



    for (int i = 0; i < desc->height; ++i) {
        for (int j = 0; j < desc->width; ++j) {

        }
    }
}

ImageDescription read_ifd(vector<uint8_t> data_reader, const TiffHeader* header) {
    auto position = header->ifd_offset  /* + sizeof(TiffHeader)*/;
    auto tag_count = (data_reader[position + 1] << 8) | data_reader[position];
    // cout << tag_count << " Found Tags" << std::endl;
    ImageDescription description;
    auto offset = header->ifd_offset + 2;
    for (int i = 0; i < tag_count; ++i) {
        auto ifd_data = slice(data_reader, offset, offset + IfdEntrySize);
        offset = offset + IfdEntrySize;
        auto ifd = reinterpret_cast<IfdEntry*>(ifd_data.data());
        // Plot Tag desciption
        // std::cout << "Ifd Tag:" << ifd->tag << ", Field Type:" << ifd->field_type << ", Count:" << ifd->count << ", Value: " << ifd->value << std::endl;
        switch (ifd->tag) {
            case TAG_BITS_PER_PIXEL:
                description.bits_per_pixel_tag = ifd->value;
                break;
            case TAG_COLOR_SHAPE:
                description.color_shape_tag = ifd->value;
                break;
            case TAG_COMPRESSION:
                description.compression_tag = ifd->value;
                break;
            case TAG_IMAGE_HEIGHT:
                description.height = ifd->value;
                break;
            case TAG_IMAGE_WITH:
                description.width = ifd->value;
                break;
            case TAG_SAMPLES_PER_PIXEL:
                description.sample_per_pixel = ifd->value;
                break;
            default:
                break;
        }
    }

    auto pixel_data = slice(data_reader, sizeof(TiffHeader), header->ifd_offset);
    for (auto byte: pixel_data) {
        description.pixel_bytes.push_back(byte);
    }
    return description;
}

void analyse_data(char *raw_data, int data_length) {
    std::cout << data_length << " Bytes read" << std::endl;
    auto data = reinterpret_cast<unsigned char *>(raw_data);
    vector<uint8_t> data_reader(data, data + data_length);

    /***
     * Plot Bytes
    int count = 0;
    for (auto en: data_reader) {
        std::cout << std::format("{:04d}:{:02X} ",count, en);
        count++;
    }
    std::cout << std::endl << "======" << std::endl; */

    // Read Header
    auto header_data = slice(data_reader, 0, 8);
    auto header = reinterpret_cast<TiffHeader *>(header_data.data());
    std::cout << "Header byte_order:" << std::format("{:X}", header->byte_order) << " Id:"
              << format("{:d}", header->tiff_id) << " IFD offset:" << format("{:d}", header->ifd_offset) << std::endl;
    if (header->tiff_id != TIFF_ID && header->tiff_id != 43) {
        std::cout << "File data does not seem to be TIF formatted" << std::endl;
        return;
    }

    // Read fist IFD (Page)
    auto images_description = read_ifd(data_reader, header);
    describe_tiff(&images_description);
}


#endif //TIFF_READER_TIFF_READER_H
