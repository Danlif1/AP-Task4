//
// Created by lenovo on 1/24/2023.
//

#include "SocketIO.h"

//constructor
SocketIO::SocketIO(int client_socket) : client_socket(client_socket) {}

void SocketIO::write(std::string text) {
    int sent_bytes = send(this->client_socket, text.c_str(), text.size(), 0);
    if (sent_bytes < 0) {
        perror("error sending message");
    }
    text.clear();
}

std::string SocketIO::read() {
    std::string temp_data;
    char fu = 0;
    int n = recv(this->client_socket, &fu, sizeof(char), 0);
    while (fu != '\n') {
        if (n < 0) {
            std::cerr << "ERROR reading from socket" << std::endl;
            exit(1);
        } else {
            temp_data += fu;
            n = recv(this->client_socket, &fu, sizeof(char), 0);
        }
    }
    return temp_data;
}
