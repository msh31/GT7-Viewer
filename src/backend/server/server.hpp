#pragma once
#include <backend/packet/packet.hpp>
#include <backend/socket.hpp>

#define MAX_UDP_PAYLOAD_SIZE 65507 /* max IPv4 UDP payload (65535 - 20 IP - 8 UDP headers) */

class CServer {
    public:
        ~CServer( ) {
            if ( m_is_server_running ) {
                stop( );
            }
        }

        bool start( );
        void listen( );

        SOCKET get_socket( ) const { return m_socket; };
        Packet::A get_latest_packet_a( ) const {
            std::lock_guard lock( m_packet_mutex );
            Packet::A packet = m_packet_a;
            return packet;
        };

        std::atomic<bool> stop_flag{ false };

    private:
        bool stop( );

        bool m_is_server_running = false;
        int m_port = 33740;

        SOCKET m_socket;
        sockaddr_in m_server_address;

        Packet::A m_packet_a = { };
        mutable std::mutex m_packet_mutex;
};
