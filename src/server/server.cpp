#include "server.hpp"

// PUBLIC
bool CServer::start( ) {
    std::println( "[inf] starting UDP server.." );

#ifdef _WIN32
    WSADATA wsaData;
    if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 ) {
        return false;
    }
#endif

    m_server_address.sin_family = AF_INET;
    m_server_address.sin_addr.s_addr = INADDR_ANY;
    m_server_address.sin_port = htons( m_port );
    m_socket = socket( AF_INET, SOCK_DGRAM, 0 ); // SOCK_STREAM = TCP, DGRAM = UDP

    if ( m_socket == INVALID_SOCKET ) {
        return false;
    }

    if ( bind( m_socket, (struct sockaddr*)&m_server_address, sizeof( m_server_address ) ) == SOCKET_ERROR ) {
        CLOSE_SOCKET( m_socket );
        return false;
    }

    m_is_server_running = true;
    std::println( "[inf] started UDP server on port {}!", m_port );
    return true;
}

bool CServer::stop( ) {
    std::println( "[inf] stopping UDP server on port {}..", m_port );
#ifdef _WIN32
    WSACleanup( );
#endif
    if ( m_socket != INVALID_SOCKET ) {
        CLOSE_SOCKET( m_socket );
    }
    return true;
}

void CServer::listen( ) {
    char buf[MAX_UDP_PAYLOAD_SIZE];
    while ( 1 ) {
        struct sockaddr_in client;
        socklen_t clen = sizeof( client );

        ssize_t n = recvfrom( m_socket, buf, sizeof( buf ), 0, (struct sockaddr*)&client, &clen );
        if ( n < 0 ) {
            std::println( "[error] recvfrom returned less than 0 indicating a failure: {}", n );
            break;
        }

        char ip[INET_ADDRSTRLEN];
        inet_ntop( AF_INET, &client.sin_addr, ip, sizeof( ip ) );
        std::println( "[inf] received {} bytes from {}:{}", n, ip, ntohs( client.sin_port ) );
    }
}
