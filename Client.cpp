
#include <pthread.h>
#include "ClientInputCheck.h"
#include "Client.h"


void *downloadFile(void *threadInfo){
    struct threadHelper* info = (struct threadHelper*) threadInfo;
    info->client.sendToServer("valid");
    std::string full_path = "Thread" + std::to_string(pthread_self()) + info->file_path;
    std::string answer = info->client.getSOIO()->read();
    std::string file_content = info->client.receiveForDownload();
    info->client.saveToFile(file_content, full_path);
    pthread_exit(NULL);

}

Client::Client(int port, const char *ip) {
    Client::port = port;
    Client::ip = ip;
    Client::client_socket = socket(AF_INET, SOCK_STREAM, 0);
    Client::download_file = false;
    Client::stio = new StandardIO();
    Client::soio = new SocketIO(client_socket);
    if (Client::client_socket < 0) {
        std::perror("error creating socket");
    }
    memset(&(Client::remote_address), 0, sizeof(Client::remote_address));
    Client::remote_address.sin_family = AF_INET;
    Client::remote_address.sin_addr.s_addr = inet_addr(Client::ip);
    Client::remote_address.sin_port = htons(Client::port);
}


void Client::connectToServer() {
    if (connect(Client::client_socket, (struct sockaddr *) &(Client::remote_address), sizeof(Client::remote_address)) <
        0) {
        std::perror("error connecting to server");
    }

}

void Client::sendToServer(std::string input) {
    // sending data to the server
    input += "\n";
    int sent_bytes = send(this->client_socket, input.c_str(), input.size(), 0);
    if (sent_bytes < 0) {
        perror("error sending message");
    }
    input.clear();
}

bool Client::sendFile() {
    std::string file_path = stio->read();
    std::ifstream file;
    file.open(file_path);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            sendToServer(line);
        }
        file.close();
        sendToServer("$");
        return true;
    } else {
        file.close();
        sendToServer("file not found");
        return false;
    }
}

void Client::saveToFile(std::string file_content, std::string file_name) {
    std::ofstream MyFile(file_name);
    MyFile << file_content;
    MyFile.close();
}

bool Client::isPathValid(std::string file_path) {
    std::ifstream file(file_path);
    if (file) {
        return true;
    } else {
        return false;
    }
}

bool Client::receiveInput() {
    receiveFromServer();
    std::string input = stio->read();
    sendToServer(input);
    if (input == "1") {
        receiveFromServer();
        if (sendFile()) {
            receiveFromServer();
            sendFile();
            receiveFromServer();
            return true;
        } else {
            return true;
        }
    } else if (input == "2") {
        receiveFromServer();
        receiveFromServer();
        return true;
    } else if (input == "3") {
        receiveFromServer();
        return true;
    } else if (input == "4") {
        receiveFromServer();
        return true;
    } else if (input == "5") {
        receiveFromServer();
        if (download_file) {
            std::string file_path = stio->read();
            if (isPathValid(file_path)) {
                //TODO: Thread function
                pthread_t thread;
                struct threadHelper info = {*this , file_path};
                pthread_create(&thread, NULL, downloadFile, (void *)&info);
                return true;
            } else {
                sendToServer("invalid");
                receiveFromServer();
                return true;
            }
            return true;
        } else {
            return true;
        }
    } else if (input == "8") {
        closeSocket();
        return false;
    } else {
        return true;
    }
}

void Client::closeSocket() {
    close(Client::client_socket);
}

void Client::receiveFromServer() {
    std::string answer = "";
    char fu = 0;
    int n = recv(this->client_socket, &fu, sizeof(char), 0);
    bool need_input = false;
    if (fu == '*') {
        need_input = true;
        n = recv(this->client_socket, &fu, sizeof(char), 0);
    } else if (fu == '&') {
        this->download_file = true;
        n = recv(this->client_socket, &fu, sizeof(char), 0);
    }
    while (fu != '$') {
        if (n < 0) {
            std::cerr << "ERROR reading from socket" << std::endl;
            exit(1);
        } else {
            answer += fu;
            n = recv(this->client_socket, &fu, sizeof(char), 0);
        }
    }
    std::cout << answer << std::endl;
    if (need_input) {
        std::string input = stio->read();
        sendToServer(input);
    }
    return;
}

std::string Client::receiveForDownload() {
    std::string answer = "";
    char fu = 0;
    int n = recv(this->client_socket, &fu, sizeof(char), 0);
    while (fu != '$') {
        if (n < 0) {
            std::cerr << "ERROR reading from socket" << std::endl;
            exit(1);
        } else {
            answer += fu;
            n = recv(this->client_socket, &fu, sizeof(char), 0);
        }
    }
    return answer;
}


