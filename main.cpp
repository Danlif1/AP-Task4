#include <regex>
#include <iostream>
#include "KNN.h"
#include "AlgorithmSettings.h"
#include "SocketIO.h"
#include "StandardIO.h"
#include "CLI.h"
#include "ClassifyData.h"
#include  "DisplayResult.h"
#include "Client.h"
#include "ClientInputCheck.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>


void read_file(std::string &file_name) {
    std::ifstream fin;
    fin.open(file_name);
    if (!fin.is_open()) {
        //Error Message
        std::cout << "Could not open the file " << file_name << std::endl;
        std::cout << "Error code: " << strerror(errno) << std::endl;
    }
}

int main(int argc, char **argv) {
    KNN *knn = new KNN();
//SocketIO* socketIo = new SocketIO(1);
    StandardIO *standardIo = new StandardIO();
    if (!inputCheck(argc, argv)) {
        std::perror("Invalid input");
        return 0;
    }
    CLI *cli = new CLI(standardIo, knn);
    cli->start();
    Client client(atoi(argv[2]), argv[1]);
    client.connectToServer();
    while (client.receiveInput()) {}
    client.~Client();
    return 0;
}

