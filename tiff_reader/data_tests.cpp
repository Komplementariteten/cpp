//
// Created by me on 03.12.23.
//
#include <catch2/catch_test_macros.hpp>

#include "test_data.hpp"

TEST_CASE("export_is_ok", "[exporter]") {
    SECTION("HAS CORRECT WIDTH") {
        REQUIRE(SLIDER4.width == 240);
    }
    SECTION("HAS CORRECT HEIGHT") {
        REQUIRE(SLIDER4.width == 320);
    }
    SECTION("HAS CORRECT PIXELCOUNT") {
        auto count = 0;
        for(auto a: SLIDER4.pixel) {
            ++count;
        }

        REQUIRE(count == (320*240));
    }
}