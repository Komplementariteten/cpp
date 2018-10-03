#include <iostream>
#include <boost/asio/io_service.hpp>
#include "NetScannerLib/netscanner.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
    try {
        if (argc != 2) {
            std::cerr << "Usage: ping <host>" << std::endl;
#if !defined(BOOST_WINDOWS)
            std::cerr << "(You may need to run this programm ad root.)" << std::endl;
#endif
            return 1;
        }

        boost::asio::io_service io_service;
        netscanner n(io_service, argv[1]);
        io_service.run();
    }catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}