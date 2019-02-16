//
// Created by Will nicht on 2019-01-26.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../net.h"

int TestServerSocketBind() {
    auto connection = komplement::net::serve_tcp(55);
    return 0;
}

TEST_CASE("TestServerSocketBind (pass)", "[net::connect]"){
    REQUIRE_NOTHROW(TestServerSocketBind());
}