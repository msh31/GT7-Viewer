#pragma once
#include <utils/socket.hpp>

#define MAX_UDP_PAYLOAD_SIZE 65507 /* max IPv4 UDP payload (65535 - 20 IP - 8 UDP headers) */

class CServer {
    public:
        ~CServer( ) {
            if ( m_is_server_running ) {
                stop( );
            }
        }

        bool start( );
        bool stop( );
        void listen( );

        SOCKET get_socket( ) const { return m_socket; };

    private:
        bool m_is_server_running = false;
        int m_port = 33740;

        SOCKET m_socket;
        sockaddr_in m_server_address;
};
