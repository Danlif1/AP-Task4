//
// Created by Daniel Lifshitz on 14/01/2023.
//

#ifndef AP_TASK4_COMMAND_H
#define AP_TASK4_COMMAND_H


#include <string>
#include "DefaultIO.h"

class Command {
private:
    DefaultIO& dio;
protected:
    std::string description; // description in the menu.
    std::string instruction; // the message shown after the command is chosen.
    std::string getDes();

    DefaultIO &getDio() const;
public:
    Command(DefaultIO &dio);
    virtual void execute() = 0;
    virtual ~Command();
    virtual void printDesc();
    virtual void printInst();

    const std::string &getDescription() const;

    const std::string &getInstruction() const;

};


#endif //AP_TASK4_COMMAND_H
