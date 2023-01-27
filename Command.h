//
// Created by lenovo on 1/24/2023.
//

#ifndef UNTITLED1_COMMAND_H
#define UNTITLED1_COMMAND_H
#include <string>
#include "SocketIO.h"
#include "KNN.h"

class Command {
public:
    std::string description;
    std::string instruction;
    DefaultIO* dio;
    KNN* knn;
    virtual void execute() = 0;
    //destructor
    virtual ~Command() = default;
};


#endif //UNTITLED1_COMMAND_H
