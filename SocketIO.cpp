//
// Created by lenovo on 1/11/2023.
//

#include "SocketIO.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>

void SocketIO::write(double d) {
//send to client
}

void SocketIO::write(std::string text) {
    if (SocketIO::sendTo(text) < 0) {
        perror("error sending message");
    }
}

int SocketIO::sendTo(const std::string& text) {

    return send(this->client_socket, text.c_str(), text.size() + 1, 0);
}

std::string SocketIO::read() {
    memset(&(buffer), 0, sizeof(buffer));
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(this->client_socket, buffer, expected_data_len, 0);
    if (read_bytes < 0) {
        std::perror("error reading from socket");
    } else if (read_bytes == 0) {
        // if connection to server is closed we end the program
        std::perror("server disconnected");
    } else {
        return std::string(buffer);
    }
}


void SocketIO::sendFile(std::fstream &file_s, long file_size) {
    size_t sent = 0;
    std::string line;
    send_int(file_size);
    long left = file_size;
    long sum = 0;
    char buffer[CHUNK_SIZE];
    while (left > 0) {
        long sending = (CHUNK_SIZE < left) ? CHUNK_SIZE : left;
        file_s.read(buffer, sending);
        sent = send(this->client_socket, buffer, sending, 0);
        if (sent < 0) {
            std::cout << "Server : Error sending file." << std::endl;
        } else {
            sum += sent;
        }
        left -= sent;
    }
}