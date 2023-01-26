//
// Created by lenovo on 1/24/2023.
//

#ifndef UNTITLED1_SOCKETIO_H
#define UNTITLED1_SOCKETIO_H

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
public:
    bool error = false;

    SocketIO(int client_socket);

    std::string read() override;

    void write(std::string text) override;
};




#endif //UNTITLED1_SOCKETIO_H
