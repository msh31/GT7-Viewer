#include "heartbeat.hpp"

bool CHeartBeat::send( SOCKET socket, char buffer ) {
    auto res =
        sendto( socket, &buffer, sizeof( buffer ), 0, (struct sockaddr*)&m_target_address, sizeof( m_target_address ) );
    return res == sizeof( buffer );
}
