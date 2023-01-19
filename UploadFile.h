//
// Created by Daniel Lifshitz on 18/01/2023.
//

#ifndef AP_TASK4_UPLOADFILE_H
#define AP_TASK4_UPLOADFILE_H

#include "Command.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "PointReader.h"


class UploadFile : public Command {
private:
    std::string instruction2;
public:
    UploadFile(DefaultIO &dio, KNN &knn) : Command(dio, knn) {
        description = "1. upload an unclassified csv file\n";
        instruction = "Please upload your local train CSV file.";
        instruction2 = "Please upload your local test CSV file.";
    };
    const std::string &getInstruction(int);
    void execute() override;
};



#endif //AP_TASK4_UPLOADFILE_H
