#include <iostream>
#include "ServerSocket.h"

using namespace serialization_tests;

int main() {
    std::cout << "Starting Server!" << std::endl;
    Container<meta_info, data_item>* c = new Container<meta_info, data_item>(128);
    c->meta_info->Y = 55;
    c->meta_info->flag = 8;
    auto ss = new ServerSocket<meta_info, data_item>(*c);
    ss->Wait();
    std::this_thread::sleep_for(std::chrono::minutes(2));
    return 0;
}
