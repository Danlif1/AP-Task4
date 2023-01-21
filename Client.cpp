
#include "ClientInputCheck.h"
#include "Client.h"

#include <utility>

Client::Client(int port, const char *ip) {
    Client::port = port;
    Client::ip = ip;
    Client::client_socket = socket(AF_INET, SOCK_STREAM, 0);
    Client::stio = new StandardIO();
    Client::soio = new SocketIO(client_socket);
    if (Client::client_socket < 0) {
        std::perror("error creating socket");
    }
    memset(&(Client::remote_address), 0, sizeof(Client::remote_address));
    Client::remote_address.sin_family = AF_INET;
    Client::remote_address.sin_addr.s_addr = inet_addr(Client::ip);
    Client::remote_address.sin_port = htons(Client::port);
}


void Client::connectToServer() {
    if (connect(Client::client_socket,(struct sockaddr *) &(Client::remote_address), sizeof(Client::remote_address)) < 0) {
        std::perror("error connecting to server");
    }

}

void Client::sendToServer(std::string input) {
    // sending data to the server
    soio->write(input);
}

bool Client::receiveInput() {
    std::string input;
    input = stio->read();
    if (input == "1") {
        //TODO: Read from file and send to server function
        return true;
    } else if (input == "5") {
        //TODO: Send to server and download from server function
        return true;
    } else if (input == "8") {
        soio->write(input);
        closeSocket();
        return false;
    } else {
        Client::sendToServer(input);
        return true;
    }
}

void Client::closeSocket() {
    close(Client::client_socket);
}

void Client::receiveFromServer() {
    std::string input = soio->read();
    stio->write(input);
}
