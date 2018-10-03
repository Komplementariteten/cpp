//
// Created by Will nicht on 30.09.18.
//

#ifndef GEOLOGGER_UDP_SERVER_H
#define GEOLOGGER_UDP_SERVER_H

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/udp.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

namespace GeoLogger {
    class udp_server {
    public:
        udp_server(io_service& service);
        bool isOpen();
    private:
        void receive();

        void handle_receive(const boost::system::error_code &ec, std::size_t bytes_transfered);

        udp::socket m_socket;
        udp::endpoint m_remote;
        boost::array<char, 1> m_buffer;

    };
}

#endif //GEOLOGGER_UDP_SERVER_H
