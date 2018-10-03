//
// Created by Will nicht on 10.05.18.
//

#ifndef NETSCANNER_NETSCANNER_H
#define NETSCANNER_NETSCANNER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include "icmp_header.h"
#include "ipv4_header.h"

class netscanner {
public:
    void testsocket() {

    }
    netscanner(boost::asio::io_context& ic, const char* destination)
            : m_resolver(ic), m_socket(ic, boost::asio::ip::icmp::v4()), m_timer(ic),
              m_sequence(0), m_replies(0) {
        m_destination = *m_resolver.resolve(boost::asio::ip::icmp::v4(), destination, "").begin();
        start_send();
        start_receive();
    }
private:
    void start_send() {
        std::string body("Hello from my ping.");
        icmp_header echo_request;
        echo_request.type(icmp_header::echo_request);
        echo_request.code(0);
        echo_request.identifier(get_identifier());
        echo_request.sequence_number(++m_sequence);
        compute_checksum(echo_request, body.begin(), body.end());

        // Encoding the Request?
        boost::asio::streambuf request_buffer;
        std::ostream os(&request_buffer);
        os << echo_request << body;

        // Sending the Request
        m_sendtime = boost::posix_time::microsec_clock::universal_time();
        m_socket.send_to(request_buffer.data(), m_destination);

        // wait up to five seconds for a reply
        m_replies = 0;
        m_timer.expires_at(m_sendtime + boost::posix_time::seconds(5));
        m_timer.async_wait(boost::bind(&netscanner::handle_timeout, this));

    }

    void handle_timeout()
    {
        if (m_replies == 0)
            std::cout << "Request timed out" << std::endl;

        // Requests must be sent no less than one second apart.
        m_timer.expires_at(m_sendtime + boost::posix_time::seconds(1));
        m_timer.async_wait(boost::bind(&netscanner::start_send, this));
    }

    void start_receive()
    {
        // Discard any data already in the buffer.
        m_reply.consume(m_reply.size());

        // Wait for a reply. We prepare the buffer to receive up to 64KB.
        m_socket.async_receive(m_reply.prepare(65536),
                              boost::bind(&netscanner::handle_receive, this, _2));
    }

    void handle_receive(std::size_t length)
    {
        // The actual number of bytes received is committed to the buffer so that we
        // can extract it using a std::istream object.
        m_reply.commit(length);

        // Decode the reply packet.
        std::istream is(&m_reply);
        ipv4_header ipv4_hdr;
        icmp_header icmp_hdr;
        is >> ipv4_hdr >> icmp_hdr;

        // We can receive all ICMP packets received by the host, so we need to
        // filter out only the echo replies that match the our identifier and
        // expected sequence number.
        if (is && icmp_hdr.type() == icmp_header::echo_reply
            && icmp_hdr.identifier() == get_identifier()
            && icmp_hdr.sequence_number() == m_sequence)
        {
            // If this is the first reply, interrupt the five second timeout.
            if (m_replies++ == 0)
                m_timer.cancel();

            // Print out some information about the reply packet.
            boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();
            std::cout << length - ipv4_hdr.header_length()
                      << " bytes from " << ipv4_hdr.source_address()
                      << ": icmp_seq=" << icmp_hdr.sequence_number()
                      << ", ttl=" << ipv4_hdr.time_to_live()
                      << ", time=" << (now - m_sendtime).total_milliseconds() << " ms"
                      << std::endl;
        }

        start_receive();
    }
    static unsigned short get_identifier()
    {
#if defined(BOOST_WINDOWS)
        return static_cast<unsigned short>(::GetCurrentProcessId());
#else
        return static_cast<unsigned short>(::getpid());
#endif
    }

    boost::asio::ip::icmp::resolver m_resolver;
    boost::asio::ip::icmp::endpoint m_destination;
    boost::asio::ip::icmp::socket m_socket;
    boost::asio::deadline_timer m_timer;
    unsigned short m_sequence;
    boost::posix_time::ptime m_sendtime;
    boost::asio::streambuf m_reply;
    std::size_t m_replies;
};


#endif //NETSCANNER_NETSCANNER_H
