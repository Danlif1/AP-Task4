//
// Created by lenovo on 1/17/2023.
//

#ifndef AP_4_ALGORITHSETTINGS_H
#define AP_4_ALGORITHSETTINGS_H


#include "Command.h"

class AlgorithmSettings : public Command {
private:


    std::string validK(const std::string &s);

    std::string validMetric(const std::string &s);

    std::string answerToClient(std::vector<std::string> v);

    std::vector<std::string> split(const std::string &str, char delimiter);

    void updateSettings(std::vector<std::string> v, std::string &answer);

public:
    AlgorithmSettings(DefaultIO* dio, KNN* knn);

    void execute() override;
};


#endif //AP_4_ALGORITHSETTINGS_H
