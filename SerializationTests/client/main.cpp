//
// Created by Will nicht on 08.10.20.
//

#include <iostream>
#include "client.h"

int main(){
    std::cout << "Starting Client!" << std::endl;
    auto c = new serialization_tests::SerializationClient();
    c->Connect( "127.0.0.1");
}
