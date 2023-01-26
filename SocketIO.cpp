//
// Created by lenovo on 1/24/2023.
//

#include "SocketIO.h"

//constructor
SocketIO::SocketIO(int client_socket) : client_socket(client_socket) {}

void SocketIO::write(std::string text) {
    int sent_bytes = send(this->client_socket, text.c_str(), text.size() + 1, 0);
    if (sent_bytes < 0) {
        perror("error sending message");
    }
    text.clear();
}

std::string SocketIO::read() {
//    memset(&(buffer), 0, sizeof(buffer));
//    int expected_data_len = sizeof(buffer);
//    int read_bytes = recv(this->client_socket, buffer, expected_data_len, 0);
//    if (read_bytes < 0) {
//        std::perror("error reading from socket");
//        return "";
//    } else if (read_bytes == 0) {
//        // if connection to server is closed we end the program
//        std::perror("server disconnected");
//        return "";
//    } else {
//        return buffer;
//    }
    std::string temp_data = "";
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
