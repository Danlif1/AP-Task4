//
// Created by Daniel Lifshitz on 18/01/2023.
//

#ifndef AP_TASK4_UPLOADFILE_H
#define AP_TASK4_UPLOADFILE_H

#include "Command.h"
#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include "../PointFiles/PointReader.h"


class UploadFile : public Command {
private:
    std::string insturction2;
public:
    UploadFile(SocketIO &dio, KNN &knn) : Command(dio, knn) {
        description = "1. upload an unclassified csv file\n";
        instruction = "Please upload your local train CSV file.";
        insturction2 = "Please upload your local test CSV file.";
    };
    const std::string &getInstruction(int);
    void execute() override;
};



#endif //AP_TASK4_UPLOADFILE_H
