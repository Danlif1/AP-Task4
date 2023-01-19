//
// Created by lenovo on 1/11/2023.
//

#include "SocketIO.h"

void SocketIO::write(double d) {
//send to client
}

void SocketIO::write(std::string text) {
//send to client
}

std::string SocketIO::read() {
    //read from client
}


void SocketIO::sendFile(std::fstream &file_s, long file_size) {
    size_t sent = 0;
    std::string line;
    send_int(file_size);
    long left = file_size;
    long sum = 0;
    char buffer[CHUNK_SIZE];
    while(left > 0) {
        long sending = (CHUNK_SIZE<left)? CHUNK_SIZE: left;
        file_s.read(buffer, sending);
        sent = send(client_sock, buffer, sending, 0);
        if (sent < 0) {
            std::cout << "Server : Error sending file." << std::endl;
        } else {
            sum += sent;
        }
        left -= sent;
    }
}