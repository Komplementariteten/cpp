//
// Created by Will nicht on 08.10.20.
//

#ifndef SERIALIZATIONTESTS_CLIENT_H
#define SERIALIZATIONTESTS_CLIENT_H
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include "../include/functions.h"
#include "../include/datatypes.h"

namespace serialization_tests{
    const int SERVER_PORT = 65112;
    const int RCV_BUFFER_SIZE = 65507;
    const int DELIMITER_SIZE = 8;
    class SerializationClient{
    public:
        SerializationClient():buffer_(RCV_BUFFER_SIZE), frames_found_(0){
        }
        SerializationClient(const SerializationClient &client) = delete;
        ~SerializationClient(){}
        SerializationClient &operator=(SerializationClient &client) = delete;
        SerializationClient &&operator=(SerializationClient &&client) {
            throw "this is buggy";
        }
        void Connect(std::string server_addr){
            socket_ = this->ConntectToLoopBack(server_addr);
            this->active_ = true;
            this->StartRead();
        }
    private:
        int socket_{};
        bool active_;
        int frames_found_;
        std::vector<std::byte> buffer_;
        void StartRead(){
            while (this->active_){
                int numOfBytes = recv(socket_, buffer_.data(), RCV_BUFFER_SIZE, 0);
                if(numOfBytes < 1){
                    // possible disco from server
                } else {
                    FindSeperatorAndTranslate();
                }
            }
        }
        void FindSeperatorAndTranslate() {
            int i = 0;
            for(auto byte_ptr = this->buffer_.begin(); byte_ptr != this->buffer_.end(); byte_ptr++, i++) {
                auto sep = *reinterpret_cast<u_long *>(&buffer_[i]);
                if(sep == SEPERATOR_VALUES){
                    std::cout << "+";
                    byte_ptr += sizeof(sep);
                    i += sizeof(sep);
                    auto meta = from_bytes<meta_info>(&buffer_[i], sizeof(meta_info));
                    std::cout << "found meta " << + meta->flag << std::endl;
                    this->frames_found_++;
                    byte_ptr += sizeof(meta_info);
                    i += sizeof(meta_info);
                }
            }
            std::cout << this->frames_found_ << " frames found -> next buffer" << std::endl;
        }
        int ConntectToLoopBack(std::string server_addr) {
            struct sockaddr_in serveradr;
            bzero(&serveradr, sizeof(serveradr));
            serveradr.sin_family = AF_INET;
            serveradr.sin_port = htons(SERVER_PORT);
            auto sock_fp = socket(AF_INET, SOCK_STREAM, 0);
            auto inetSuccess = inet_aton(server_addr.c_str(), &serveradr.sin_addr);
            if(!inetSuccess) {
                throw server_addr + " is no valid ip address";
            }
            connect(sock_fp, reinterpret_cast<const sockaddr *>(&serveradr), sizeof(serveradr));
            return sock_fp;
        }
    };
}

#endif //SERIALIZATIONTESTS_CLIENT_H
