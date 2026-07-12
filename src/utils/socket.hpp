#pragma once
#ifdef _WIN32
    #include <winsock2.h> //enables network programming
    #include <ws2tcpip.h> //for inet_pton(), enebles modern IP address conversion

    #define CLOSE_SOCKET( s ) closesocket( s )
    #define SOCKADDR_CAST ( SOCKADDR* )
    #define SOCKET_ERROR ( -1 )
    #define SOCKLEN_T int
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <unistd.h>

    #define CLOSE_SOCKET( s ) close( s )
    #define SOCKET int
    #define INVALID_SOCKET ( -1 )
    #define SOCKADDR_CAST ( struct sockaddr* )
    #define SOCKET_ERROR ( -1 )
    #define SOCKLEN_T socklen_t
#endif

class CSocket {
    public:
        CSocket( SOCKET socket ) : m_socket( socket ) {}

        ~CSocket( ) {
            if ( m_socket != INVALID_SOCKET ) CLOSE_SOCKET( m_socket );
        }

        operator SOCKET( ) const { return m_socket; }

        CSocket( const CSocket& ) = delete;
        CSocket& operator=( const CSocket& ) = delete;

    private:
        SOCKET m_socket;
};
