//
// Created by Will nicht on 26.09.18.
//
#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <gtest/gtest.h>
#include <thread>
#include <list>

using namespace boost::asio;
using namespace boost::asio::ip;


TEST(AsyncIOServer, Mulitthread) {
    ASSERT_TRUE(true);
}


/* Coroutine 1 is now deprecated
 *
 * unsigned short port = 20220;
io_service ioService;
tcp::endpoint tcp_endpoint {tcp::v6(), port};
tcp::acceptor tcp_acceptor {ioService, tcp_endpoint};
std::list<tcp::socket> tcp_sockets;

io_service clientIo;
tcp::resolver resolv {clientIo};
tcp::socket tcp_socket{clientIo};


void do_write(tcp::socket &tcp_socket, yield_context context) {
    std::time_t now = std::time(nullptr);
    std::string data = std::ctime(&now);
    async_write(tcp_socket, buffer(data), context);
    tcp_socket.shutdown(tcp::socket::shutdown_send);
}

void do_accept(yield_context context) {
    for (int i = 0; i < 2; ++i) {
        tcp_sockets.emplace_back(ioService);
        tcp_acceptor.async_accept(tcp_sockets.back(), context);
        spawn(ioService, [](yield_context yield) {
            do_write(tcp_sockets.back(), yield);
        });
    }
}

void do_connect(const boost::system::error_code &ec) {
    if (!ec) {
        std::array<char, 4096> bytes;
        EXPECT_EQ(bytes.size(), 0);
        tcp_socket.async_read_some(buffer(bytes), [bytes](const boost::system::error_code &ec, std::size_t bytes_transferred) {
            EXPECT_GT(bytes.size(), 1);
        });
    }
}


TEST (ThreadTest, BaseThreadding) {
    io_service ioService;
    std::thread t1{[](){
        thread_callback();
    }};
    t1.join();
}

TEST (ThreadTest, TCPThreading) {
    tcp_acceptor.listen();
    spawn(ioService, do_accept);
    ioService.run();

    for (int i = 0; i < 10; ++i) {
        tcp::resolver::query q{"[::]", std::to_string(port)};
        resolv.async_resolve(q, do_connect);
        clientIo.run();
    }
} */