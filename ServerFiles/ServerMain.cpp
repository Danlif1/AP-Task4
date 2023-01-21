// Server side C/C++ program to demonstrate Socket
// programming
#include <stdlib.h>
#include <string.h>
#include "PointFiles/PointReader.h"
#include "Server.h"


/**
 * @brief The main function of the server
 * 
 * @param argc Should have file and port by that order.
 * @param argv Should be 3.
 * @return int Returning 0 if there is a problem with the inputs.
 */
int main(int argc, char const* argv[]) {

    Server server(atoi(argv[1]));
    while(true) {
        server.connectToClient();
    }
    server.closeSocket();
    delete &server;
    return 0;
}
