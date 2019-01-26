//
// Created by Will nicht on 2019-01-26.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../net.h"

int TestServerSocketBind() {
    komplement::net::connect::serve_tcp(55);
    return 0;
}

TEST_CASE("TestServerSocketBind (pass)", "[net::connect]"){
    REQUIRE_NOTHROW(TestServerSocketBind());
}