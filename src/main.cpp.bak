#include <heartbeat/heartbeat.hpp>
#include <server/server.hpp>

int main( ) {
    CServer server;
    if ( !server.start( ) ) {
        std::println( "[error] failed to start UDP server!" );
        return -1;
    }

    auto socket = server.get_socket( );

    std::string ps4_ip = "192.168.178.36";
    int ps4_port = 33739;
    char payload = 'A'; // packet A

    CHeartBeat heartbeat( ps4_ip, ps4_port );
    if ( !heartbeat.send( socket, payload ) ) {
        std::println( "[error] failed to send heartbeat with payload: {}", payload );
        return -1;
    }
    std::println( "[inf] sent heartbeat: {}", payload );

    server.listen( ); // blocking
    return 0;
}
