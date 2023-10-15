#include <iostream>
#include <fstream>
#include <array>
#include <format>
#include <vector>
#include <cstdint>

using namespace std;

template<int left = 0, int right = 0, typename T>
constexpr auto slice(T &&container) {
    if constexpr (right > 0) {
        return std::span(begin(std::forward<T>(container)) + left, begin(std::forward<T>(container)) + right);
    } else {
        return std::span(begin(std::forward<T>(container)) + left, end(std::forward<T>(container)) + right);
    }
}

struct TiffHeader {
    uint16_t byte_order;
    uint16_t tiff_id;
    int32_t ifd_offset;
};

struct IfdEntry {
    uint16_t tag;
    uint16_t field_type;
    uint32_t count;
    uint32_t value;
};

const unsigned short TIFF_ID = 42;
constexpr int IfdEntrySize = sizeof(struct IfdEntry);

template<typename T>
auto slice(T &&container, int left, int right) {
    if (right > 9) {
        return std::span(begin(std::forward<T>(container)) + left, begin(std::forward<T>(container)) + right);
    }else {
        return std::span(begin(std::forward<T>(container)) + left, end(std::forward<T>(container)) + right);
    }
}

void read_ifd(vector<uint8_t> data_reader, const TiffHeader* header) {
    auto position = header->ifd_offset  /* + sizeof(TiffHeader)*/;
    auto tag_count = (data_reader[position + 1] << 8) |data_reader[position];
    cout << tag_count << " Found Tags" << std::endl;
    auto offset = header->ifd_offset + 2;
    for (int i = 0; i < tag_count; ++i) {
        auto ifd_data = slice(data_reader, offset, offset + IfdEntrySize);
        offset = offset + IfdEntrySize;
        auto ifd = reinterpret_cast<IfdEntry*>(ifd_data.data());
        std::cout << "Ifd Tag:" << ifd->tag << ", Field Type:" << ifd->field_type << ", Count:" << ifd->count << ", Value: " << ifd->value << std::endl;

    }
}

void read_tags(vector<uint8_t> data_reader, const TiffHeader* header) {
    auto position = header->ifd_offset  + sizeof(TiffHeader);
    while (position < data_reader.size()) {
        auto ifd_data = slice(data_reader, position, position + IfdEntrySize);
        position = position + IfdEntrySize;
        auto ifd = reinterpret_cast<IfdEntry*>(ifd_data.data());
        std::cout << "Ifd Tag:" << ifd->tag << ", Field Type:" << ifd->field_type << ", Count:" << ifd->count << ", Value offset: " << ifd->value << std::endl;

    }
}


void analyse_data(char *raw_data, int data_length) {
    std::cout << data_length << " Bytes read" << std::endl;
    auto data = reinterpret_cast<unsigned char *>(raw_data);
    vector<uint8_t> data_reader(data, data + data_length);
    int count = 0;
    for (auto en: data_reader) {
        std::cout << std::format("{:04d}:{:02X} ",count, en);
        count++;
    }
    std::cout << std::endl << "======" << std::endl;

    // Read Header
    auto header_data = slice<0, 8>(data_reader);
    auto header = reinterpret_cast<TiffHeader *>(header_data.data());
    std::cout << "Header byte_order:" << std::format("{:X}", header->byte_order) << " Id:"
              << format("{:d}", header->tiff_id) << " IFD offset:" << format("{:d}", header->ifd_offset) << std::endl;
    if (header->tiff_id != TIFF_ID && header->tiff_id != 43) {
        std::cout << "File data does not seem to be TIF formated" << std::endl;
        return;
    }

    // Read fist IFD (Page)
    read_ifd(data_reader, header);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Wrong number of Arguments: Call " << argv[0] << " ./" << argv[0] << " image-file-to-open"
                  << std::endl;
        return -1;
    }
    auto file_name = std::string(argv[1]);
    if (!file_name.ends_with(".tif") | file_name.ends_with(".tiff")) {
        std::cout << "Wrong file type, provide a tif File";
        return -1;
    }

    ifstream file(file_name, ios::in | ios::binary | ios::ate);
    if (file.is_open()) {
        auto size = file.tellg();
        std::cout << "reading " << size << " of bytes" << std::endl;
        auto memblock = new char[size];
        file.seekg(0, ios::beg);
        file.read(memblock, size);
        analyse_data(memblock, size);
        file.close();
    }
    return 0;
}
