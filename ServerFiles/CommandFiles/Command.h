//
// Created by Daniel Lifshitz on 14/01/2023.
//

#ifndef AP_TASK4_COMMAND_H
#define AP_TASK4_COMMAND_H


#include <string>
#include "../../SocketFiles/SocketIO.h"
#include "../KNNFiles/KNN.h"
class Command {
private:


protected:
    std::string description; // description in the menu.
    std::string instruction; // the message shown after the command is chosen.
    std::string getDes();

    DefaultIO &getDio() const;

    SocketIO &dio;
    KNN &knn;
public:
    Command(SocketIO &dio, KNN &knn);

    virtual void execute() = 0;

    virtual ~Command();

    void printDesc();

    void printInst();

    const std::string &getDescription() const;

    const std::string &getInstruction() const;

};


#endif //AP_TASK4_COMMAND_H
