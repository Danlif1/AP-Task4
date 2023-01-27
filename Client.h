//
// Created by lenovo on 1/2/2023.
//

#ifndef AP_TASK3_CLIENT_H
#define AP_TASK3_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "StandardIO.h"
#include "SocketIO.h"



class Client {
    int port;
    const char *ip;
    int client_socket;
    struct sockaddr_in remote_address;
    bool isPathValid(std::string file_path);
    StandardIO *stio;
    SocketIO *soio;
    char buffer[4096];
    bool download_file;

    void closeSocket();
    bool sendFile();

public:
    Client(int port, const char *ip);
    void sendToServer(std::string input);
    std::string receiveForDownload();
    void saveToFile(std::string file_content, std::string file_name);
    void connectToServer();
    bool receiveInput();
    void receiveFromServer();
    SocketIO *getSOIO(){
        return soio;
    }

    ~Client() = default;
};

void *downloadFile(void *);

struct threadHelper {
    Client client;
    std::string file_path;
};

#endif //AP_TASK3_CLIENT_H
