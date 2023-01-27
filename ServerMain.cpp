// Server side C/C++ program to demonstrate Socket
// programming
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Server.h"
#include <regex>

/**
 * @brief The main function of the server
 *
 * @param argc Should have file and port by that order.
 * @param argv Should be 3.
 * @return int Returning 0 if there is a problem with the inputs.
 */
bool isValidPort(std::string port) {
    for (int i = 0; i < port.size(); ++i) {
        if (!isdigit(port[i])) {
            return false;
        }
    }
    if (std::stoi(port) < 0 || std::stoi(port) > 65535) {
        return false;
    }
    return true;
}

int main(int argc, char const* argv[]) {
    if (isValidPort(argv[1])){
        Server server = Server(atoi(argv[1]));
        server.connectToClient();
        server.closeSocket();
        server.~Server();
        return 0;
    } else {
        std::cout << "Invalid port" << std::endl;
        return 0;
    }

}
