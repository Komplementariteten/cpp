//
// Created by me on 03.11.23.
//

#ifndef TIFF_READER_CONTRACTS_H
#define TIFF_READER_CONTRACTS_H

struct RGBPixel {
    unsigned char red;
    unsigned char blue;
    unsigned char green;
};

class ImageDescription {
public:
    ImageDescription(): width(0), height(0), compression_tag(0), color_shape_tag(0), bits_per_pixel_tag(0), sample_per_pixel(0) {};
    std::vector<RGBPixel *> pixels;
    std::uint16_t width;
    std::uint16_t height;
    std::uint16_t compression_tag;
    std::uint16_t color_shape_tag;
    std::uint16_t bits_per_pixel_tag;
    std::uint16_t sample_per_pixel;
};

#endif //TIFF_READER_CONTRACTS_H
