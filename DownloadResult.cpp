//
// Created by Daniel Lifshitz on 19/01/2023.
//

#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include "DownloadResult.h"
#include "SocketIO.h"


/**
 * @brief Construct a new Download Result:: Download Result object.
 *
 * @param dio DefaultIO used.
 * @param knn The knn class used.
 */
DownloadResult::DownloadResult(DefaultIO *dio, KNN *knn) {
    description = "5. download results\n";
    this->dio = dio;
    this->knn = knn;
}

void DownloadResult::send() {
    for (int i = 0; i < knn->getAllLabels().size(); i++) {
        int place = i + 1;
        std::string result = std::to_string(place) + "\t" + knn->getAllLabels()[i] + "\n";
        dio->write(result);
    }
    dio->write("$");
}

void *sendInNewSock(void *dth) {
    downloadThreadHelper* tmp = (downloadThreadHelper*) dth;
    int download_socket_server = tmp->socket_server;
    DownloadResult* downloadResult = tmp->downloadResult;

    struct sockaddr_in download_client_address;
    unsigned int download_client_len = sizeof(download_client_address);
    if (listen(download_socket_server, 5) < 0) {
        perror("error listening on socket");
    }
    int download_client_sock = accept(download_socket_server,
                                      (struct sockaddr *) &(download_client_address), &(download_client_len));
    if (download_client_sock < 0) {
        perror("error accepting connection");
    } else {
        SocketIO* s = new SocketIO(download_client_sock);
        for (int i = 0; i < downloadResult->knn->getAllLabels().size(); i++) {
            int place = i + 1;
            std::string result = std::to_string(place) + "\t" + downloadResult->knn->getAllLabels()[i] + "\n";
            s->write(result);
        }
        s->write("$");
    }
    close(download_client_sock);
    close(download_socket_server);
    pthread_exit(NULL);
}

/**
 * @brief Executing the command.
 *
 */
void DownloadResult::execute() {
    if (knn->getUnclassifiedData().empty()) {
        dio->write("please upload data");
        dio->write("$");
        return;
    } else if (knn->getAllLabels().empty()) {
        dio->write("please classify the data");
        dio->write("$");
        return;
    } else {
        dio->write("&");
        dio->write("Please enter file path");
        dio->write("$");
        if (dio->read() == "valid") {
            pthread_t thread;

            int port = 0;
            int download_socket_server = socket(AF_INET, SOCK_STREAM, 0);
            if (download_socket_server < 0) {
                std::cout << "Error creating socket" << std::endl;
                exit(1);
            }

            struct sockaddr_in download_server_address;
            socklen_t sa_len = sizeof(download_server_address);
            memset(&(download_server_address), 0, sizeof(download_server_address));
            download_server_address.sin_family = AF_INET;
            download_server_address.sin_addr.s_addr = INADDR_ANY;
            download_server_address.sin_port = htons(port);
            if ((bind(download_socket_server,
                      (struct sockaddr *) &(download_server_address), sizeof(download_server_address))) < 0) {
                perror("error binding socket");
            }
            struct sockaddr_in tmp_download_server_address;

            if (getsockname(download_socket_server, (sockaddr*) &tmp_download_server_address, &sa_len) == -1) {
                perror("getsockname() failed");
            }

            dio->write(std::to_string((int) ntohs(tmp_download_server_address.sin_port)) + "\n");
            struct downloadThreadHelper* dth = new downloadThreadHelper();
            dth->socket_server = download_socket_server;
            dth->downloadResult = this;
            pthread_create(&thread, NULL, sendInNewSock, (void *)dth);
        } else {
            dio->write("invalid path");
            dio->write("$");
        }
    }

}