//
// Created by Will nicht on 25.09.18.
//

#include <gtest/gtest.h>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

unsigned short port = 20220;

class udp_server {
public:
    udp_server(io_service& service): m_socket(service, udp::endpoint(udp::v6(), 50501)){
    }
    bool Socket_IsOpen() {
        return m_socket.is_open();
    }
private:
    void receive() {
        m_socket.async_receive_from(buffer(m_buffer), m_remote,
                boost::bind(&udp_server::handle_receive,
                        this,
                        placeholders::error,
                        placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code &ec, std::size_t bytes_transfered) {
        if (!ec || ec == boost::asio::error::message_size) {
            boost::shared_ptr<std::string> message(new std::string("OK"));
            m_socket.async_send_to(buffer(*message), m_remote, bind(&udp_server::handle_send, this, message, placeholders::error, placeholders::bytes_transferred));
        }
    }

    void handle_send(boost::shared_ptr<std::string> /* message */,
            const boost::system::error_code& /* error */,
            std::size_t /* bytes_transferred */ ) {    }

    udp::socket m_socket;
    udp::endpoint m_remote;
    boost::array<char, 1> m_buffer;
};


TEST(BoostSockets, TCPIpV6) {
    io_service ioService;
    tcp::endpoint tcp_endpoint {tcp::v6(), port};
    tcp::acceptor tcp_acceptor {ioService, tcp_endpoint};
    tcp::socket tcp_sock {ioService};
    EXPECT_TRUE(tcp_endpoint.protocol() == tcp::v6());
    EXPECT_TRUE(tcp_endpoint.port() == port);
}

TEST(BoostSockets, UDPIpV6) {
    io_service service;
    udp_server server(service);
    service.run();
    ASSERT_TRUE(server.Socket_IsOpen());
    /* udp::resolver resolver(clientService);
    udp::resolver::query query(udp::v6(), "::1", "50501");
    udp::resolver::iterator udp_ite = resolver.resolve(query);
    udp::endpoint client_endpoint = *udp_ite;
    udp::socket cSock(clientService, client_endpoint);
    boost::array<char, 4086> recv_buff;
    cSock.async_receive_from(buffer(recv_buff), client_endpoint, [this](const boost::system::error_code ec, std::size_t len) {
        ASSERT_GT(len, 0);
    });*/
}