
#include "main.h"

using namespace std;


void add_tiff_in_folder(exporter::Export& ex, const std::string& folder) {
    for(auto const& dir_entry: filesystem::directory_iterator {folder}) {
        auto can_read = dir_entry.is_regular_file();
        can_read |= dir_entry.path().has_extension();
        can_read |= dir_entry.path().extension() == "tif";
        can_read |= dir_entry.path().extension() == "tiff";
        if(can_read)
            ex.add_image(dir_entry.path());
        else
            std::cout << dir_entry.path() << " not added" << std::endl;
    }
}

int main(const int argc, const char *argv[]) {
    exporter::Export exporter;

    cmdtools::reg("dir", "directory to look for tif files", [&exporter](const std::string& arg) {
        add_tiff_in_folder(exporter, arg);
    });

    cmdtools::reg("target", "target header file to export to", [&exporter](const std::string& arg) {
        exporter.add_target(arg);
    });

    cmdtools::parse(argc, argv);
    exporter.finish();
    return 0;
}
