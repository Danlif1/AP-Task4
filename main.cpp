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

bool sendFile() {
    std::string file_path;
    std::cout << "Please enter file path" << std::endl;
    getline(std::cin, file_path);
    std::ifstream file;
    file.open(file_path);
    if (file.is_open()) {
        std::string line = "";
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
        std::cout << "$" << std::endl;
        return true;
    } else {
        std::cout << "$" << std::endl;
        return false;
    }
}

int main(int argc, char **argv) {
    KNN *knn = new KNN();
//SocketIO* socketIo = new SocketIO(1);

bool isFile = sendFile();
if (isFile) {
    std::cout << "File sent successfully" << std::endl;
} else {
    std::cout << "File not sent" << std::endl;
}
//    StandardIO *standardIo = new StandardIO();
//    CLI *cli = new CLI(standardIo, knn);
//    cli->start();
//    UploadFile *uploadFile = new UploadFile(standardIo, knn);
//    while(true){
//        uploadFile->execute();
//    }
    return 0;
}

