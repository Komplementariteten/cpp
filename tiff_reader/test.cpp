//
// Created by me on 14.10.23.
//

#include <catch2/catch_test_macros.hpp>
struct IfdEntry {
    uint16_t tag;
    uint16_t field_type;
    uint32_t count;
    uint32_t value_or_offset;
};

TEST_CASE("sizeof", "[sizeof]") {
    REQUIRE(sizeof(short int) == 2);
    REQUIRE(sizeof(std::uint16_t) == 2);
    REQUIRE(sizeof(std::int16_t) == 2);
    REQUIRE(sizeof(struct IfdEntry) == 12);
}