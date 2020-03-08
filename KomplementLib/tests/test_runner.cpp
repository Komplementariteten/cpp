//
// Created by Will nicht on 2019-01-26.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../net.h"

using namespace komplement;

int TestServerSocketBind() {
    auto connection = net::serve_tcp(55);
    return 0;
}

int TestBindListenAndSigInt() {
    auto s = net::serve_tcp(550);
/*
    auto processing_fnc = [](char data[net::DATABUFFER_SIZE]) -> std::unique_ptr<std::vector<char>> {
        std::unique_ptr<std::vector<char>> ptr(new std::vector<char>(data, data + sizeof(data) / sizeof(data[0])));
        return ptr;
    };
    auto runner = net::run(s, processing_fnc);
*/
}

TEST_CASE("TestServerSocketBind (pass)", "[net::connect]"){
    REQUIRE_NOTHROW(TestServerSocketBind());
}

TEST_CASE("Hanlde Functype is correct Definded", "[net::connect]") {


}