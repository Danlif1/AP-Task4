//
// Created by lenovo on 1/11/2023.
//

#ifndef AP_4_SOCKETIO_H
#define AP_4_SOCKETIO_H

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include "DefaultIO.h"

class SocketIO : public DefaultIO {
    int client_socket;

    char buffer[4096];

    int sendTo(const std::string &text);

public:
    SocketIO(int client_socket) : client_socket(client_socket) {};

    void write(double d) override;

    int send_int(int num) const;

    void write(std::string text) override;

    static long getFileSize(const std::string &filename);

    void sendFile(std::fstream &file_s, long file_size); //full file stream

    std::string read() override;


};


#endif //AP_4_SOCKETIO_H
