//
// Created by me on 11.11.23.
//

#include "exporter.h"

namespace exporter {
    namespace {
        // examples
        const RGBPixel SOME_PIXEL[]{{4, 5, 7}, {1, 2, 3}};
        const RGBPixelExport Export{100, 100, {{4, 5, 7}, {1, 2, 3},}};
        const std::regex FRegex("[^\\W]+", std::regex_constants::ECMAScript | std::regex_constants::icase);
    }

    Export::Export(): target_set_(false) {
    }

    void Export::add_target(const std::string& target_file) {
        this->target_file_ = target_file;
        this->target_set_ = true;
    }


    void Export::add_image(const std::string&source_file) {
        std::cout << "Adding images " << source_file << " to the export " << std::endl;
        const auto img_desc = tiff_reader::read_tiff_file(source_file);
        const auto export_name = filename_to_exportname(source_file);
        this->export_ += get_export_text(img_desc, export_name);
    }

    void Export::finish() const {
        if(!this->target_set_)
            return;
        std::cout << "Writing to: " << this->target_file_ << std::endl;
        const auto s = EXPORT_HEADER + this->export_;
        std::ofstream outstream(this->target_file_, std::ios::app | std::ios::trunc);
        outstream << s << std::endl;
        outstream.close();
    }

    std::string filename_to_exportname(const std::string&file_name) {
        std::filesystem::path p(file_name);
        p.replace_extension("");
        auto fname = p.filename().string();
        std::string clean_name;
        const auto end = std::sregex_iterator();
        for (std::sregex_iterator i(fname.begin(), fname.end(), FRegex); i != end; ++i) {
            const std::smatch&match = *i;
            clean_name += match.str();
        }
        for (auto&c: clean_name) c = static_cast<char>(toupper(c));
        return clean_name;
    }

    std::string get_export_text(const ImageDescription&img, const std::string&type_name) {
        std::string s;
        setlocale(LC_ALL, "german");
        s += "const RGBPixelExport ";
        s += type_name + " {\n";
        s += std::format("{},{},", img.width, img.height) + "{";
        for (const auto pixel: img.pixels) {
            s += "{" + std::format("{},{},{}", pixel.red, pixel.green, pixel.blue) + "},";
        }
        s += R"(}}
)";
        return s;
    }
}
