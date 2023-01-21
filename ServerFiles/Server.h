//
// Created by lenovo on 1/2/2023.
//

#ifndef AP_TASK3_SERVER_H
#define AP_TASK3_SERVER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "PointFiles/PointReader.h"
#include "KNNFiles/KNN.h"
#include "CLI.h"
#include "../SocketFiles/StandardIO.h"
#include "../SocketFiles/SocketIO.h"




class Server {
    int port;
    int socket_server;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    unsigned int client_len = sizeof(client_address);
    char buffer[4096];


    void bindSocket();


public:
    Server(int port);
    void connectToClient();
    void closeSocket();


};




#endif //AP_TASK3_SERVER_H
