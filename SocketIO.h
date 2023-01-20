//
// Created by lenovo on 1/11/2023.
//

#ifndef AP_4_SOCKETIO_H
#define AP_4_SOCKETIO_H


#include "DefaultIO.h"

class SocketIO : public DefaultIO {
    int client_socket;

    int sendTo(const std::string& text);

    char buffer[4096];
public:
    SocketIO(int client_socket) : client_socket(client_socket) {};

    void write(double d) override;

    void write(std::string text) override;

    void sendFile(std::fstream &file_s, long file_size); //full file stream
    std::string read() override;
};


#endif //AP_4_SOCKETIO_H
