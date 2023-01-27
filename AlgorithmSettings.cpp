//
// Created by lenovo on 1/17/2023.
//

#include "AlgorithmSettings.h"
#include <string>
#include <vector>
#include <regex>

AlgorithmSettings::AlgorithmSettings(DefaultIO* dio, KNN* knn){
this->dio = dio;
this->knn = knn;
this->description = "2. algorithm settings\n";
this->instruction = "";
};

void AlgorithmSettings::execute() {
    dio->write("*");
    dio->write("The current KNN parameters are: K = " + std::to_string(knn->getK()) +
                     ", distance metric = " + knn->getMetric());
    dio->write("$");
    std::string response = dio->read();
    std::vector<std::string> v = split(response, ' ');
    std::string answer = answerToClient(v);
    updateSettings(v, answer);

}

std::vector<std::string> AlgorithmSettings::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::string AlgorithmSettings::validK(const std::string &s) {
    std::regex re("^[1-9][0-9]*$");
    if (!std::regex_match(s, re) || this->knn->getClassifiedData().empty()) {
        return  "invalid value for k\n";
    } else if (std::stoi(s) < this->knn->getClassifiedData().size()) {
        return "";
    } else {
        return "invalid value for k\n";
    }
}

std::string AlgorithmSettings::validMetric(const std::string &s) {
    std::regex re("^(AUC|MAN|CHB|CAN|MIN)$");
    return std::regex_match(s, re) ? "" : "invalid value for metric";
}

std::string AlgorithmSettings::answerToClient(std::vector<std::string> v) {
    if (v.size() != 2) {
        return "invalid input";
    } else {
        std::string answer;
        answer += validK(v[0]);
        answer += validMetric(v[1]);
        return answer;
    }
}

void AlgorithmSettings::updateSettings(std::vector<std::string> v, std::string &answer) {
    if  (answer == "") {
        knn->setK(std::stoi(v[0]));
        knn->setMetric(v[1]);
        dio->write("$");
    } else {
        dio->write(answer);
        dio->write("$");
    }

}
