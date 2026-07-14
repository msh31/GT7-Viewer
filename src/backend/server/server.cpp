#include "server.hpp"
#include <cerrno>

// PUBLIC
bool CServer::start( ) {
    SPDLOG_INFO( "[inf] starting UDP server.." );

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

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    auto res = setsockopt( m_socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof( tv ) );
    if ( res < 0 ) {
        SPDLOG_ERROR( "[error]: setsockopt failed with error code: {}", errno );
        return false;
    }

    m_is_server_running = true;
    SPDLOG_INFO( "[inf] started UDP server on port {}!", m_port );
    return true;
}

bool CServer::stop( ) {
    SPDLOG_INFO( "[inf] stopping UDP server on port {}..", m_port );
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

    auto key = Packet::get_key_bytes( );
    while ( !stop_flag.load( ) ) {
        struct sockaddr_in client;
        socklen_t clen = sizeof( client );

        ssize_t n = recvfrom( m_socket, buf, sizeof( buf ), 0, (struct sockaddr*)&client, &clen );
        if ( n < 0 ) {
            if ( errno == EAGAIN || errno == EWOULDBLOCK ) {
#ifndef NDEBUG
                SPDLOG_INFO( "[info] recvfrom returned a timeout: {}", errno );
#endif
                continue; // just a timeout, loop back and recheck stop_flag
            }
            SPDLOG_ERROR( "[error] recvfrom returned: {}", errno );
            break;
        }
        char ip[INET_ADDRSTRLEN];
        inet_ntop( AF_INET, &client.sin_addr, ip, sizeof( ip ) );
#ifndef NDEBUG
        SPDLOG_INFO( "[info] received {} bytes from {}:{}", n, ip, ntohs( client.sin_port ) );
#endif
        auto buffer = reinterpret_cast<uint8_t*>( buf );
        if ( n != 296 ) {
            SPDLOG_ERROR( "[error] received {} bytes when 296 were expected!", n );
            continue;
        }
        std::span<uint8_t, 296> output( buffer, n );

        auto nonce = Packet::derive_nonce( output );
        auto decrypted_packet = Packet::decrypt( output, key, nonce );

        // std::println( "{}", std::span( decrypted_packet ).first( 16 ) );

        std::lock_guard lock( m_packet_mutex );
        m_packet_a = Packet::parse( decrypted_packet );

#ifndef NDEBUG
        SPDLOG_INFO( "[info] parsed a packet!" );
#endif
        // std::println( "Speed: {}", packet_a.speed );
        // std::println( "Lap: {}/{}", packet_a.lapCount, packet_a.totalLaps );
    }
}
