//
// Created by Will nicht on 02.10.20.
//

#ifndef SERIALIZATIONTESTS_SERVERSOCKET_H
#define SERIALIZATIONTESTS_SERVERSOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <c++/v1/vector>
#include <c++/v1/thread>
#include <c++/v1/iostream>
#include "../include/datatypes.h"
#include "../include/functions.h"

namespace serialization_tests {
    const int SERVER_SOCK_PORT = 65112;

    template<typename T1, typename T2>
    class ServerSocket {
    public:
        explicit ServerSocket(Container<T1, T2> &container) : buffer_(), clientPool_(0),
                                                              is_accepting(true) {
            buffer_size_ = container.size;
            buffer_ = as_bytes(container, buffer_size_);
            // auto new_container = from_bytes<Container<T1, T2>, int>(buffer_, container.size, container.items.size());
            auto sock_fp = ConnectTooLoopBack();
            std::cout << "Starting with " << std::thread::hardware_concurrency() << " max concurrent threads" << std::endl;
            acceptHandle_ = std::thread([=] { this->StartAcceptHandle(sock_fp); });
        };

        ServerSocket(const ServerSocket &serverSocket) = delete;

        ServerSocket(ServerSocket &&serverSocket) {
            serverSocket_ = serverSocket.serverSocket_;
            buffer_ = serverSocket.buffer_;
            serverSocket.buffer_.clear();
            serverSocket.serverSocket_ = 0;
            throw "this is buggy";
            /* for(auto it = serverSocket.clientPool_.begin(); it!= serverSocket.clientPool_.end(); it++){
            }
            clientPool_ = serverSocket.clientPool_;
            acceptHandle_ = std::move(serverSocket.acceptHandle_);
            serverSocket.clientPool_.clear();
            serverSocket.clientPool_.clear(); */
        }

        ServerSocket() = default;

        ~ServerSocket() {
            acceptHandle_.join();
            close(this->serverSocket_);
        }

        void Wait() {};

        ServerSocket &operator=(ServerSocket &serverSocket) = delete;

        ServerSocket &&operator=(ServerSocket &&serverSocket) {
            buffer_ = serverSocket.buffer_;
            serverSocket_ = serverSocket.serverSocket_;
            serverSocket.buffer_.clear();
            serverSocket.serverSocket_ = 0;
            throw "this is buggy";
        }

    private:
        int serverSocket_{};
        std::vector<std::thread> clientPool_;
        char* buffer_;
        size_t buffer_size_;
        std::thread acceptHandle_;
        bool is_accepting{};

        auto ConnectTooLoopBack() {
            struct sockaddr_in serveradr;
            bzero(&serveradr, sizeof(serveradr));
            serveradr.sin_family = AF_INET;
            serveradr.sin_addr.s_addr = htonl(INADDR_ANY);
            serveradr.sin_port = htons(SERVER_SOCK_PORT);
            auto sock_fp = socket(AF_INET, SOCK_STREAM, 0);
            bind(sock_fp, reinterpret_cast<const sockaddr *>(&serveradr), sizeof(serveradr));
            listen(sock_fp, 20);
            this->serverSocket_ = sock_fp;
            return sock_fp;
        }

        void StartAcceptHandle(int socket_fp){
            std::cout << "+";
            struct sockaddr_in client;
            auto len = sizeof(client);
            for (; is_accepting;) {
                auto client_fp = accept(socket_fp, (struct sockaddr *) (&client), (socklen_t *) &len);
                clientPool_.push_back(std::thread([=] { this->HandleClientConnection(client_fp); }));
            }
        }

        void HandleClientConnection(int socket_fp){
            for (auto i = 0; i < 100; i++) {
                std::cout << "-";
                auto content = ".";
                send(socket_fp, buffer_, buffer_size_, 0);
            }
            close(socket_fp);
            std::cout << std::this_thread::get_id() << " done " << std::endl;
        }
    };
}

#endif //SERIALIZATIONTESTS_SERVERSOCKET_H
