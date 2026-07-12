#include <server/server.hpp>

int main( ) {
    CServer server;
    server.start( );
    server.listen( ); // blocking
    return 0;
}
