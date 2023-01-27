//
// Created by lenovo on 1/17/2023.
//

#ifndef AP_TASK4_CLI_H
#define AP_TASK4_CLI_H

#include "DefaultIO.h"
#include "Command.h"
#include "UploadFile.h"
#include "AlgorithmSettings.h"
#include "ClassifyData.h"
#include "DisplayResult.h"
#include "DownloadResult.h"
#include <map>


class CLI {
    std::map<int,Command *> commands;
    DefaultIO* dio;
    KNN* knn;
    bool should_continue;
    void printMenu();
    void waitForInput();
    bool isValidInput(std::string input);

public:
    CLI(DefaultIO* dio, KNN* knn);

    void start();

    ~CLI() = default;
};


#endif //AP_TASK4_CLI_H
