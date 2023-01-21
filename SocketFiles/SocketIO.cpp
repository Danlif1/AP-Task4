//
// Created by lenovo on 1/11/2023.
//


#include <sys/stat.h>
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

int SocketIO::send_int(int num) const
{
    int32_t conv = htonl(num);
    char *data = (char*)&conv;
    int left = sizeof(conv);
    int rc;
    do {
        rc = send(client_sock, data, left, 0);
        if (rc < 0) {
            std::cout << "Error sending size." << std::endl;
            return -1;
        }
        else {
            data += rc;
            left -= rc;
        }
    }
    while (left > 0);
    return 0;
}


//FROM STACK OVERFLOW: https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c?noredirect=1&lq=1
void SocketIO::sendFile(std::fstream &file_s, long file_size) {
    size_t sent = 0;
    std::string line;
    send_int(file_size);
    long left = file_size;
    long sum = 0;
    while(left > 0) {
        long sending = (4096<left)? 4096: left;
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

long SocketIO::getFileSize(const std::string &filename) {
    struct stat stat_buf{};
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
