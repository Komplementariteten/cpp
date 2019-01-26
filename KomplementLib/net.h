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
#include "type_tools.h"

namespace komplement {
    namespace net {

        typedef int socket_fd;
        typedef int address_family;
        typedef int socket_type;
        typedef int port_number;

        class connect {
            socket_fd fd;
            address_family af;
            socket_type type;
            port_number port;
        public:

            const static connect serve_tcp(const port_number&& port) {
                connect sock;
                sock.af = AF_INET;
                sock.type = SOCK_STREAM;
                sock.fd = socket(sock.af, sock.type, 0);

                struct sockaddr_in address;
                // if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, ))

                address.sin_family = sock.af;
                address.sin_addr.s_addr = sock.type;
                address.sin_port = htons(port);

                if(bind(sock.fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
                    // error
                    close(sock.fd);
                    throw;
                }

                return sock;
            }
        };

    }
}
#endif //KOMPLEMENTLIB_NET_H
