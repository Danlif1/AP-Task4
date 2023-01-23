//
// Created by Daniel Lifshitz on 23/01/2023.
//

#ifndef AP_TASK4_SOCKETFILE_H
#define AP_TASK4_SOCKETFILE_H


#include "SocketIO.h"


class SocketFile {
private:
    const int port_no;
    int server_sock;
    struct sockaddr_in client_sin;
public:
    explicit SocketFile(int port_no);

    void setServerSock(int serverSock);
    int accept();
    void close();
};


#endif //AP_TASK4_SOCKETFILE_H
