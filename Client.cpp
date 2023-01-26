
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
    input += "\n";
    int sent_bytes = send(this->client_socket, input.c_str(), input.size(), 0);
    if (sent_bytes < 0) {
        perror("error sending message");
    }
    input.clear();
}

bool Client::sendFile() {
    std::cout << "Please enter file path:" << std::endl;
    std::string file_path = stio->read();
    stio->write(file_path);
    std::ifstream file;
    file.open(file_path);
    if (file.is_open()) {
        std::cout << "file is open" << std::endl;
        std::string line;
        while (getline(file, line)) {
            sendToServer(line);
            std::cout << line << std::endl;
        }
        file.close();
        sendToServer("$");
        std::cout << "Finished Reading File" << std::endl;
        return true;
    } else {
        file.close();
        sendToServer("$");
        std::cout << "file not found" << std::endl;
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
            receiveFromServer();
            return true;
        }
    } else if (input == "2") {
        receiveFromServer();
        sendToServer(stio->read());
        std::cout << "waiting for response" << std::endl;
        receiveFromServer();
        return true;
    } else if (input == "3") {
        std::cout << "lets get this party started" << std::endl;
        receiveFromServer();
        std::cout << "we have left the building" << std::endl;
        return true;
    } else if (input == "4") {
        std::string answer = soio->read();
        if (answer == "*") {
            receiveFromServer();
            do {
                sendToServer(stio->read());
                answer = soio->read();
            } while (answer != "$");
            return true;
        } else {
            receiveFromServer();
            return true;
        }
    } else if (input == "5") {
        if (soio->read() == "*") {
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
    } else {
        return true;
    }
}

void Client::closeSocket() {
    close(Client::client_socket);
}

void Client::receiveFromServer() {
//    std::string response = soio->read();
//    std::string response;
//    while (answer != "$") {
//        response += answer;
//        answer = soio->read();
//    }
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
    std::cout << answer << std::endl;
    std::cout << "finished reading from server" << std::endl;
    return;
}
