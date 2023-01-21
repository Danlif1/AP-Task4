//
// Created by lenovo on 1/17/2023.
//

#ifndef AP_TASK4_CLI_H
#define AP_TASK4_CLI_H

#include "../SocketFiles/DefaultIO.h"
#include "CommandFiles/Command.h"
#include "CommandFiles/UploadFile.h"
#include "CommandFiles/AlgorithmSettings.h"
#include "CommandFiles/ClassifyData.h"
#include "CommandFiles/DisplayResult.h"
#include "CommandFiles/DownloadResult.h"
#include <map>


class CLI {
    std::map<int,Command *> commands;
    DefaultIO &dio;
    KNN &knn;
    std::string printMenu();
    void waitForInput();
    bool isValidInput(std::string input);
public:
    CLI(SocketIO &dio, KNN &knn) : dio(dio), knn(knn) {
        this->dio = dio;
        this->knn = knn;
        commands.insert({1, new UploadFile(dio, knn)});
        commands.insert({2, new AlgorithmSettings(dio, knn)});
        commands.insert({3, new ClassifyData(dio, knn)});
        commands.insert({4, new DisplayResult(dio, knn)});
        commands.insert({5, new DownloadResult(dio, knn)});
        //TODO: add exit command

    };

    void start();

    ~CLI() = default;
};


#endif //AP_TASK4_CLI_H
