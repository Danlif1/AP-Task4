//
// Created by lenovo on 1/17/2023.
//

#ifndef AP_4_ALGORITHSETTINGS_H
#define AP_4_ALGORITHSETTINGS_H


#include "Command.h"

class AlgorithSettings : public Command {
private:

public:
    AlgorithSettings(DefaultIO &dio, KNN &knn) : Command(dio, knn) {};

    std::vector<std::string> split(const std::string &str, char delimiter);

    std::string validK(const std::string &s);

    std::string validMetric(const std::string &s);

    std::string answerToClient(std::vector<std::string> v);

    virtual void execute() override;
};


#endif //AP_4_ALGORITHSETTINGS_H
