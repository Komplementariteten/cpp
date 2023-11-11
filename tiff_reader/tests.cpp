//
// Created by me on 14.10.23.
//

#include <catch2/catch_test_macros.hpp>

#include "cmd_tools.h"
#include "exporter.h"

struct IfdEntry {
    uint16_t tag;
    uint16_t field_type;
    uint32_t count;
    uint32_t value_or_offset;
};

class  CallbackTest {
    bool state;
public:
    CallbackTest(): state(false) {};
    void set_called() {
        this->state = true;
    }
    [[nodiscard]] bool is_called() const {
        return this->state;
    }
};

TEST_CASE("sizeof", "[sizeof]") {
    REQUIRE(sizeof(short int) == 2);
    REQUIRE(sizeof(std::uint16_t) == 2);
    REQUIRE(sizeof(std::int16_t) == 2);
    REQUIRE(sizeof(struct IfdEntry) == 12);
}

TEST_CASE("filename_to_exportname", "[exporter]") {
    SECTION("ABSOLUTE_PATH_WITH_EXTENSION") {
        auto text = exporter::filename_to_exportname("/c/b/abc.TIFF");
        REQUIRE(text == "ABC");
    }
    SECTION("ABSOLUTE_PATH_WITHOUT_EXTENSION") {
        auto text = exporter::filename_to_exportname("/c/b/ABC");
        REQUIRE(text == "ABC");
    }
    SECTION("RELEATIVE_PATH_WITHOUT_EXTENSION") {
        auto text = exporter::filename_to_exportname("./c/b/ABC");
        REQUIRE(text == "ABC");
    }
    SECTION("UTF8_RELEATIVE_PATH_WITH_EXTENSION") {
        auto text = exporter::filename_to_exportname("./😀/c&[/bü/a-b_c😀.jpeg");
        REQUIRE(text == "AB_C");
    }
}

TEST_CASE("get_export_text", "[exporter]") {
    RGBPixel pixel1 = {0,255,0};
    RGBPixel pixel2 = {0,78,55};
    const ImageDescription description {10, 20, {&pixel1, &pixel2}};
    SECTION("EXPORT TEXT CONTAINS NAME") {
        const auto text = exporter::get_export_text(description, "ABC");
        REQUIRE(text.starts_with("const RGBPixelExport ABC {"));
    }
    SECTION("EXPORT TEXT CONTAINS WIDTH AND HEIGHT") {
        const auto text = exporter::get_export_text(description, "ABC");
        REQUIRE(text.find("{10,20,") != std::string::npos);
    }
    SECTION("EXPORT TEXT CONTAINS PIXELS IN ORDER") {
        const auto text = exporter::get_export_text(description, "ABC");
        REQUIRE(text.find("{0,255,0},{0,78,55}") != std::string::npos);
    }

}

TEST_CASE("parse_executes_callback", "[cmd_tools]") {
    const char* argv[] = {"123", "abc", "gef", "t"};
    SECTION("EXECUTE CALLBACK WITH FULL NAME ARGUMENT") {
        CallbackTest tester;
        cmdtools::reg("123", [&tester](const std::string& arg) {
            tester.set_called();
        });
        cmdtools::parse(4, argv);
        REQUIRE(tester.is_called());
    }

}