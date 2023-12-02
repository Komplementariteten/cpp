//
// Created by me on 03.11.23.
//

#ifndef TIFF_READER_CONTRACTS_H
#define TIFF_READER_CONTRACTS_H

struct   RGBPixel {
    RGBPixel(): red(255), blue(255), green(255) {};
    RGBPixel(const unsigned char r, const unsigned char g, const unsigned char b): red(r), blue(b), green(g) {};
    unsigned char red;
    unsigned char blue;
    unsigned char green;
};

struct RGBPixelExport {
    std::uint16_t width{};
    std::uint16_t height{};
    RGBPixel pixel[];
};

class ImageDescription {
public:
    ImageDescription(const uint16_t w, const uint16_t h): width(w), height(h), compression_tag(0), color_shape_tag(0), bits_per_pixel_tag(0), sample_per_pixel(0) {};
    ImageDescription(): width(0), height(0), compression_tag(0), color_shape_tag(0), bits_per_pixel_tag(0), sample_per_pixel(0) {};
    ImageDescription(const uint16_t w, const uint16_t h, const std::vector<RGBPixel>& p): pixels(p), width(w), height(h), compression_tag(0), color_shape_tag(0), bits_per_pixel_tag(0), sample_per_pixel(0) {};
    std::vector<RGBPixel> pixels;
    std::uint16_t width;
    std::uint16_t height;
    std::uint16_t compression_tag;
    std::uint16_t color_shape_tag;
    std::uint16_t bits_per_pixel_tag;
    std::uint16_t sample_per_pixel;
};

namespace tiff_reader {
    const ImageDescription NoImageDescription = ImageDescription();
}

#endif //TIFF_READER_CONTRACTS_H
