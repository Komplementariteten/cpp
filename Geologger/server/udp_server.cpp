//
// Created by Will nicht on 30.09.18.
//

#include "udp_server.h"

namespace GeoLogger {
    const int GEOLOGGER_PORT = 5051;
    udp_server::udp_server(io_service &service): m_socket(service, udp::endpoint(udp::v6(), GEOLOGGER_PORT)) {
        // Socket Options
        // m_socket.set_option();
        receive();
    }

    void udp_server::handle_receive(const boost::system::error_code &ec, std::size_t bytes_transfered) {

    }


    void udp_server::receive() {
        m_socket.async_receive_from(buffer(m_buffer), m_remote, bind(&udp_server::handle_receive, this, placeholders::error, placeholders::bytes_transferred));
    }

    bool udp_server::isOpen() {
        return this->m_socket.is_open();
    }
}