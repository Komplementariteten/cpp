//
// Created by Will nicht on 2019-01-26.
//

#ifndef KOMPLEMENTLIB_NET_H
#define KOMPLEMENTLIB_NET_H

#include <memory>
#include <system_error>
#include <type_traits>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include "type_tools.h"

namespace komplement {
    namespace net {

        typedef int socket_fd;
        typedef int address_family;
        typedef int socket_type;
        typedef int port_number;

        struct Client {
            socket_fd  fd;
            std::function<bool (int)> data_handle;
            std::thread runner;
        };

        struct Server {
            socket_fd fd;
            address_family af;
            socket_type type;
            port_number port;
            int max_pending = 3;
            sockaddr_in sockaddr;
            socklen_t addresslen;
            std::vector<Client> clients;
        };
        
        const void thread_run_clienthandle(const Client&& client) {
            rea
        }

        const void thread_run_srvhandle(const Server&& con, std::function<bool (int)> data_handle) {
            if(listen(con.fd, con.max_pending) < 0){
                close(con.fd);
                throw;
            }
            int client_sock = 0;
            if(0 < (client_sock = accept(con.fd, (struct sockaddr *) &con.sockaddr, &con.addresslen))) {
                return;
            }
            Client client;
            client.fd = client_sock;
            client.data_handle = data_handle;
            client.runner = std::thread(thread_run_clienthandle, client);
            con.clients.push_back(client);
        }

        const Server serve_tcp(const port_number&& port) {
            Server sock;

            sock.af = AF_INET;
            sock.type = SOCK_STREAM;
            sock.fd = socket(sock.af, sock.type, 0);
            sock.port = port;

            sock.sockaddr.sin_family = sock.af;
            sock.sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            sock.sockaddr.sin_port = htons(port);
            sock.addresslen = sizeof(sock.sockaddr);
            if((bind(sock.fd, (struct sockaddr *) &sock.sockaddr, sock.addresslen)) < 0) {
                // error
                close(sock.fd);
                throw;
            }

            return sock;
        }

        const std::thread run(const Server&& con) {
            auto runner = std::thread(thread_run_srvhandle, con);
            return runner;
        }


    }
}
#endif //KOMPLEMENTLIB_NET_H
