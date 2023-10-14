#include <iostream>
#include <fstream>
#include <array>
#include <format>
#include <vector>

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
    unsigned short int byte_order;
    unsigned short int tiff_id;
    unsigned int ifd_offset;
};

struct IfdEntry {
    unsigned short int tag;
    unsigned short int field_type;
    unsigned int count;
    int value_offset;
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

void analyse_data(char *raw_data, int data_length) {
    std::cout << data_length << " Bytes read" << std::endl;
    auto data = reinterpret_cast<unsigned char *>(raw_data);
    vector<unsigned char> data_reader(data, data + data_length);
    for (auto en: data_reader) {
        std::cout << std::format("{:03d}", en) << std::endl;
    }
    std::cout << "======" << std::endl;

    // Read Header
    auto header_data = slice<0, 8>(data_reader);
    auto header = reinterpret_cast<TiffHeader *>(header_data.data());
    std::cout << "Header byte_order:" << std::format("{:X}", header->byte_order) << " Id:"
              << format("{:d}", header->tiff_id) << "IFD offset:" << format("{:d}", header->ifd_offset) << std::endl;
    if (header->tiff_id != TIFF_ID) {
        std::cout << "File data does not seem to be TIF formated" << std::endl;
        return;
    }

    // Read fist IFD (Page)
    auto ifd_data = slice(data_reader, header->ifd_offset, header->ifd_offset + IfdEntrySize);
    auto ifd1 = reinterpret_cast<IfdEntry*>(ifd_data.data());
    std::cout << "Ifd1 Tag:" << ifd1->tag << ", Field Type:" << ifd1->field_type << ", Count:" << ifd1->count << ", Value offset: "<< ifd1->value_offset << std::endl;

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
