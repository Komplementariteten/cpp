
#include "main.h"

using namespace std;

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
        auto desc = tiff_reader::analyse_tiff_data(memblock, size);
        tiff_reader::print_image_description(&desc);
        file.close();
    }
    return 0;
}
