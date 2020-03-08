//
// Created by Will nicht on 19.01.20.
//

#ifndef NETRUNNER_SERVER_H
#define NETRUNNER_SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct {
    int fd;
    struct sockaddr_in srv;
} Server;

Server* create_new();

#endif //NETRUNNER_SERVER_H
