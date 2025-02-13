//
// Created by me on 03.11.23.
//
#pragma once
#ifndef TIFF_READER_EXPORTER_H
#define TIFF_READER_EXPORTER_H

#include <filesystem>
#include <string>
#include <regex>
#include "contracts.h"
#include "export_header.h"
#include "tiff_reader.h"
#include <locale>

namespace exporter {
    std::string filename_to_exportname(const std::string& file_name);

    std::string get_export_text(const ImageDescription& img, const std::string& type_name);

    class Export {
    private:
        bool target_set_;
        std::string target_file_;
        std::string export_;

    public:
        Export();

        void add_target(const std::string& target_file);

        void add_image(const std::string& source_file);

        void finish() const;
    };
}


#endif //TIFF_READER_EXPORTER_H
