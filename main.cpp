#include <regex>
#include <iostream>
#include "KNN.h"
#include "AlgorithmSettings.h"
#include "SocketIO.h"
#include "StandardIO.h"
#include "CLI.h"
#include "ClassifyData.h"
#include  "DisplayResult.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>


void read_file(std::string& file_name){
    std::ifstream fin;
    fin.open(file_name);
    if(!fin.is_open()) {
        //Error Message
        std::cout<< "Could not open the file " << file_name << std::endl;
        std::cout<<"Error code: " << strerror(errno) << std::endl;
    }
}
int main() {
KNN* knn = new KNN();
//SocketIO* socketIo = new SocketIO(1);
StandardIO* standardIo = new StandardIO();
CLI* cli = new CLI(standardIo, knn);
cli->start();

    return 0;
}

