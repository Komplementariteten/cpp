#include "tiff_reader.h"

namespace tiff_reader {
    namespace {
        template<typename T>
        auto slice(T&&container, int left, int right) {
            if (right > 9) {
                return std::span(begin(std::forward<T>(container)) + left, begin(std::forward<T>(container)) + right);
            }
            else {
                return std::span(begin(std::forward<T>(container)) + left, end(std::forward<T>(container)) + right);
            }
        }

        ImageDescription read_ifd(std::vector<uint8_t> data_reader, const TiffHeader* header) {
            auto position = header->ifd_offset;
            auto tag_count = (data_reader[position + 1] << 8) | data_reader[position];
            std::cout << tag_count << " Found Tags" << std::endl;
            ImageDescription description;
            auto offset = position + 2;
            for (int i = 0; i < tag_count; ++i) {
                auto ifd_data = slice(data_reader, offset, offset + IfdEntrySize);
                offset = offset + IfdEntrySize;
                auto ifd = reinterpret_cast<IfdEntry *>(ifd_data.data());
                // Plot Tag desciption
                std::cout << "Ifd Tag:" << ifd->tag << ", Field Type:" << ifd->field_type << ", Count:" << ifd->count <<
                        ", Value: " << ifd->value_or_offset << std::endl;
                switch (ifd->tag) {
                    case TAG_BITS_PER_PIXEL:
                        description.bits_per_pixel_tag = ifd->value_or_offset;
                        break;
                    case TAG_COLOR_SHAPE:
                        description.color_shape_tag = ifd->value_or_offset;
                        break;
                    case TAG_COMPRESSION:
                        description.compression_tag = ifd->value_or_offset;
                        break;
                    case TAG_IMAGE_HEIGHT:
                        description.height = ifd->value_or_offset;
                        break;
                    case TAG_IMAGE_WITH:
                        description.width = ifd->value_or_offset;
                        break;
                    case TAG_SAMPLES_PER_PIXEL:
                        description.sample_per_pixel = ifd->value_or_offset;
                        break;
                    default:
                        break;
                }
            }

            auto pixels_data = slice(data_reader, sizeof(TiffHeader), header->ifd_offset);
            for (int i = 0; i < pixels_data.size(); i += description.sample_per_pixel) {
                auto pixel_data = slice(pixels_data, i, i + description.sample_per_pixel);
                auto rgb_pixel = reinterpret_cast<RGBPixel *>(pixel_data.data());
                description.pixels.push_back(rgb_pixel);
            }
            return description;
        }
    }

    ImageDescription analyse_tiff_data(char* raw_data, const long data_length) {
        // std::cout << data_length << " Bytes read" << std::endl;
        const auto data = reinterpret_cast<unsigned char *>(raw_data);
        std::vector<uint8_t> data_reader(data, data + data_length);

        // Read Header
        auto header_data = slice(data_reader, 0, 8);
        const auto header = reinterpret_cast<TiffHeader *>(header_data.data());
        // std::cout << "Header byte_order:" << std::format("{:X}", header->byte_order) << " Id:"
        //        << std::format("{:d}", header->tiff_id) << " IFD offset:" << std::format("{:d}", header->ifd_offset) << std::endl;
        if (header->tiff_id != TIFF_ID && header->tiff_id != 43) {
            std::cout << "File data does not seem to be TIF formatted" << std::endl;
            return NoImageDescription;
        }

        // Read fist IFD (Page)
        auto images_description = read_ifd(data_reader, header);
        return images_description;
    }

    void print_image_description(ImageDescription* desc) {
        if (desc->color_shape_tag != RGB_COLOR_SPACE) {
            std::cout << "TIFF uses " << desc->color_shape_tag << ", this app supports only RBG" << std::endl;
            return;
        }
        std::cout << "Width:" << desc->width << "|Height:" << desc->height << " Values per pixel:" << desc->
                sample_per_pixel << std::endl;

        for (auto pixel: desc->pixels) {
            std::cout << "RBG(" << std::format("{:d}", pixel->red) << "," << std::format("{:d}", pixel->blue) << ", " <<
                    std::format("{:d}", pixel->green) << ")" << std::endl;
        }
    }

    ImageDescription read_tiff_file(const std::string&file_path) {
        if (!file_path.ends_with(".tif") | file_path.ends_with(".tiff")) {
            return NoImageDescription;
        }
        std::ifstream fs(file_path, std::ios::in | std::ios::binary | std::ios::ate);
        if (fs.is_open()) {
            auto size = fs.tellg();
            // std::cout << "reading " << size << " of bytes" << std::endl;
            auto memblock = new char[size];
            fs.seekg(0, std::ios::beg);
            fs.read(memblock, size);
            auto desc = tiff_reader::analyse_tiff_data(memblock, size);
            fs.close();
            return desc;
        }
        return NoImageDescription;
    }
}
