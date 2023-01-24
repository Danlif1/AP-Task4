//
// Created by lenovo on 1/24/2023.
//

#include "SocketIO.h"

//constructor
SocketIO::SocketIO(int client_socket) : client_socket(client_socket) {}

int SocketIO::sendTo(const std::string &text) {

    return send(this->client_socket, text.c_str(), text.size() + 1, 0);
}

void SocketIO::write(std::string text) {
    if (SocketIO::sendTo(text) < 0) {
        perror("error sending message");
    }
}

std::string SocketIO::read() {
    memset(&(buffer), 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(this->client_socket, buffer, expected_data_len, 0);
    if (read_bytes < 0) {
        std::perror("error reading from socket");
        return "";
    } else if (read_bytes == 0) {
        // if connection to server is closed we end the program
        std::perror("server disconnected");
        return "";
    } else {
        return std::string(buffer);
    }
}