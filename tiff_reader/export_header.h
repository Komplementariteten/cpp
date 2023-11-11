//
// Created by me on 09.11.23.
//

#ifndef TIFF_READER_EXPORT_HEADER_H
#define TIFF_READER_EXPORT_HEADER_H

namespace exporter {
const std::string EXPORT_HEADER = R"include(
#pragma once

//**
// Basic pixel data Structure
//**/
struct RGBPixel {
    unsigned char red;
    unsigned char blue;
    unsigned char green;
};

//**
// Basic data Structure, the exported image is stored in
//**/
struct RGBPixelExport {
    std::uint16_t width;
    std::uint16_t height;
    RGBPixel pixel[];
};

)include";
}

#endif //TIFF_READER_EXPORT_HEADER_H
