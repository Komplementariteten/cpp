//
// Created by Will nicht on 19.01.20.
//

#include "server.h"

Server* create_tcpipserver(int server_port) {

    struct Server *s;
    bzero(&s.srv, sizeof(servaddr));
    s.srv.sin_family = AF_INET;
    s.srv.sin_addr.s_addr = htonl(INADDR_ANY);
    s.sin_port = server_port;
    s.fd = socket(AF_INET, SOCK_STREAM, 0);

    return s;
}
