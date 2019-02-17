//
// Created by Will nicht on 2019-01-26.
//

#ifndef KOMPLEMENTLIB_NET_H
#define KOMPLEMENTLIB_NET_H

#include <memory>
#include <system_error>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <iterator>
#include <thread>
#include "type_tools.h"

namespace komplement {
    namespace net {

        const int DATABUFFER_SIZE = 4096;

        typedef int socket_fd;
        typedef int address_family;
        typedef int socket_type;
        typedef int port_number;
        typedef std::function<std::unique_ptr<std::vector<char>> (const std::container* container)> processing_func;


        template <class Function, class... Args>
        class Runner {
            std::thread t;
        public:
            Runner(Function&& fnc, Args... args): t(std::thread(fnc, args...)){}
            ~Runner() {
                t.join();
            }
        };

        struct Client {
            socket_fd  fd;
            processing_func& handle;
            sockaddr_in clientadr;
        public:
            Client(processing_func&& processingFunc): handle(processingFunc) {}
        };

        struct Server {
            socket_fd fd;
            address_family af;
            socket_type type;
            port_number port;
            int max_pending = 3;
            sockaddr_in sockaddr;
            // std::vector<Client> clients;
        };

        const void thread_run_clienthandle(const Client& client) {
            char buffer[DATABUFFER_SIZE];
            if((read(client.fd, buffer, DATABUFFER_SIZE)) == 0) {
                // Disconnect
                close(client.fd);
                return ;
            }
            auto response = client.handle(std::begin(buffer), std::end(buffer));
            write(client.fd, response.get(), DATABUFFER_SIZE);
        }

        const void thread_run_srvhandle(const Server& con, processing_func data_handle) {
            void sig_int(int);
            signal(SIGINT, sig_int);
            struct sockaddr_in clientadr;
            if(listen(con.fd, con.max_pending) < 0){
                close(con.fd);
                throw;
            }
            for(;;) {
                int client_sock = 0;
                socklen_t clen = sizeof(clientadr);
                if(0 < (client_sock = accept(con.fd, (struct sockaddr *) &clientadr, &clen))) {
                    return;
                }
                Client client(thread_run_clienthandle);
                client.fd = client_sock;
                client.clientadr = clientadr;
                // con.clients.push_back(client);
            }
        }

        const Server serve_tcp(const port_number port) {
            Server sock;

            sock.af = AF_INET;
            sock.type = SOCK_STREAM;
            sock.fd = socket(sock.af, sock.type, 0);
            sock.port = port;

            sock.sockaddr.sin_family = sock.af;
            sock.sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            sock.sockaddr.sin_port = htons(port);
            socklen_t  slen = sizeof(sock.sockaddr);
            if((bind(sock.fd, (struct sockaddr *) &sock.sockaddr, slen)) < 0) {
                // error
                close(sock.fd);
                throw;
            }

            return sock;
        }

        std::unique_ptr<Runner> run(const Server& con, processing_func handle) {
            std::unique_ptr<Runner> run_ptr( new Runner(thread_run_srvhandle, con, handle));
            return run_ptr;
        }


    }
}
#endif //KOMPLEMENTLIB_NET_H
