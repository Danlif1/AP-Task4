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
#include "Point.h"


class UploadFile : public Command {
private:
    std::string insturction_2;
    std::vector<Point> getClassifiedFromClient();
    std::vector<Point> getUnclassifiedFromClient();
    bool isFileGood(std::vector<Point> input);

public:
    UploadFile(DefaultIO* dio, KNN* knn);
    void execute() override;
};



#endif //AP_TASK4_UPLOADFILE_H
