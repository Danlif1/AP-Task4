
#include "ClientInputCheck.h"
#include "Client.h"

#include <utility>

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
    if (connect(Client::client_socket,(struct sockaddr *) &(Client::remote_address), sizeof(Client::remote_address)) < 0) {
        std::perror("error connecting to server");
    }

}

void Client::sendToServer(std::string input) {
    // sending data to the server
    soio->write(input);
}

bool Client::receiveInput() {
    std::string input;
    input = stio->read();
    if(input == "1" || input == "2" || input == "3" || input == "4" ||input == "5" || input == "8"){
        switch(stoi(input)){
            case 1: {
                // Sending 1.
                Client::sendToServer(input);
                // Getting instructions.
                Client::receiveFromServer();
                // Reading file path.
                std::string filePath = stio->read();
                // If the path is good we open it and sending to the server.
                std::fstream fout;
                if (Client::receiveFromServer()) {
                    fout.open(filePath, std::ios::out | std::ios::app);
                    soio->sendFile(fout, SocketIO::getFileSize(filePath));
                } else {
                    return true;
                }
                // Getting upload complete.
                Client::receiveFromServer();
                // Getting another instruction.
                Client::receiveFromServer();
                // Reading file path.
                filePath = stio->read();
                if (Client::receiveFromServer()) {
                    fout.open(filePath, std::ios::out | std::ios::app);
                    soio->sendFile(fout,SocketIO::getFileSize(filePath));
                } else {
                    return true;
                }
                // Getting upload complete.
                Client::receiveFromServer();
                return true;
            }
            case 2: {
                // Sending 2.
                Client::sendToServer(input);
                // Getting instructions.
                Client::receiveFromServer();
                // Reading the k and the distance metric.
                std::string output = stio->read();
                Client::sendToServer(output);
                Client::receiveFromServer();
                return true;
            }
            case 3: {
                // Sending 3.
                Client::sendToServer(input);
                // Getting output.
                Client::receiveFromServer();
                return true;
            }
            case 4: {
                // Sending 4.
                Client::sendToServer(input);
                while(Client::receiveFromServer()){}
                return true;
            }
            case 5: {
                Client::sendToServer(input);
                // Getting instructions.
                Client::receiveFromServer();
                // Reading file path.
                std::string filePath = stio->read();
                if (Client::receiveFromServer()) {
                    std::string ThreadFilePath = "Thread" + std::to_string(pthread_self()) + filePath;
                    std::fstream writingFile(ThreadFilePath, std::ios::out | std::ios::in | std::ios::trunc);
                    std::string line = Client::receiveFromServerNOPRINTING();
                    while (line != "Done.") {
                        writingFile << line << std::endl;
                        std::string line = Client::receiveFromServerNOPRINTING();
                    }
                } else {
                    return true;
                }
                return true;
            }
            case 8: {
                soio->write(input);
                closeSocket();
                return false;
            }
        }
    } else {
        std::cout << "Please enter a valid number." << std::endl;
        return true;
    }
}

void Client::closeSocket() {
    close(Client::client_socket);
}

bool Client::receiveFromServer() {
    std::string input = soio->read();
    stio->write(input);
    if(input == "invalid input" || input == "please upload data" || input == "please classify the data" || input == "Done."){
        return false;
    } else {
        return true;
    }
}

std::string Client::receiveFromServerNOPRINTING() {
    std::string input = soio->read();
    return input;

}
