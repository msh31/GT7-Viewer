#pragma once
#include <backend/socket.hpp>

class CHeartBeat {
    public:
        CHeartBeat( const std::string& ip_addr, int port ) : m_ip_addr( ip_addr ), m_target_port( port ) {
            m_target_address.sin_family = AF_INET;
            inet_pton( AF_INET, m_ip_addr.c_str( ), &m_target_address.sin_addr );
            m_target_address.sin_port = htons( m_target_port );
        };

        bool send( SOCKET socket, char buffer );

    private:
        std::string m_ip_addr;
        int m_target_port;
        sockaddr_in m_target_address;
};
