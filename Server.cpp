#include "Server.h"

Server::Server(int port) {
    Server::port = port;
    Server::socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_server < 0) {
        std::cout << "Error creating socket" << std::endl;
        exit(1);
    }
    bindSocket();
}

void Server::bindSocket() {
    memset(&(Server::server_address), 0, sizeof(server_address));
    Server::server_address.sin_family = AF_INET;
    Server::server_address.sin_addr.s_addr = INADDR_ANY;
    Server::server_address.sin_port = htons(port);
    if (bind(socket_server, (struct sockaddr *) &(Server::server_address), sizeof(Server::server_address)) < 0) {
        perror("error binding socket");
    }
}

void Server::connectToClient() {
    if (listen(socket_server, 5) < 0) {
        perror("error listening on socket");
    }
//    socklen_t client_len = sizeof(client_address);
    int client_sock = accept(Server::socket_server, (struct sockaddr *) &(Server::client_address), &(Server::client_len));
    if (client_sock < 0) {
        perror("error accepting connection");
    } else {
        std::cout << "Client connected" << std::endl;
        this->dio = new SocketIO(client_sock);
        KNN knn = KNN();
        CLI cli = CLI(dio, &knn);
        cli.start();
    }

}

void Server::talk(){
    std::string answer = dio->read();
    dio->write(answer + "love, the server");
}

void Server::closeSocket(){
    close(Server::socket_server);
}




