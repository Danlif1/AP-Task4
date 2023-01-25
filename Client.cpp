
#include "ClientInputCheck.h"
#include "Client.h"

Client::Client(int port, const char *ip) {
    Client::port = port;
    Client::ip = ip;
    Client::client_socket = socket(AF_INET, SOCK_STREAM, 0);
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
    soio->write(input);
}

bool Client::sendFile() {
    std::string file_path = stio->read();
    std::ifstream file(file_path);
    if (file) {
        std::string line = "";
        while (getline(file, line)) {
            sendToServer(line);
        }
        file.close();
        sendToServer("$");
        return true;
    } else {
        sendToServer("$");
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
            return true;
        } else {
            receiveFromServer();
            return true;
        }
    } else if (input == "2") {
        receiveFromServer();
        sendToServer(stio->read());
        receiveFromServer();
        return true;
    } else if (input == "3") {
        receiveFromServer();
        return true;
    } else if (input == "4") {
        if (soio->read()=="*") {
            receiveFromServer();
            do {
                sendToServer(stio->read());
            } while (soio->read() != "$");
            return true;
        } else {
            receiveFromServer();
            return true;
        }
    } else if (input == "5") {
        if (soio->read() =="*"){
            receiveFromServer();
            std::string file_path = stio->read();
            if (isPathValid(file_path)) {
                //TODO: Thread function
                sendToServer("valid");
                std::string answer = soio->read();
                std::string file_content;
                while (answer != "$") {
                    file_content += answer;
                    answer = soio->read();
                }
                saveToFile(file_content, file_path);
                return true;
            } else {
                sendToServer("invalid");
                return true;
            }
        } else {
            //server doesn't have the results
            receiveFromServer();
            return true;
        }
    } else if (input == "8") {
        soio->write(input);
        closeSocket();
        return false;
    }
}

void Client::closeSocket() {
    close(Client::client_socket);
}

void Client::receiveFromServer() {
    std::string answer = soio->read();
    while (answer != "$") {
        stio->write(answer);
        answer = soio->read();
    }
}
