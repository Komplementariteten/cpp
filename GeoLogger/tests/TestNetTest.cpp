//
// Created by Will nicht on 22.11.18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include "catch.h"


TEST_CASE("Net Test", "[getaddrinfo]"){

    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    struct addrinfo hints, *res, *ressave;
    bzero(&hints, sizeof(struct addrinfo));
    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);

}