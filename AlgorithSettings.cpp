//
// Created by lenovo on 1/17/2023.
//

#include "AlgorithSettings.h"
#include <string>
#include <vector>
#include <regex>

void AlgorithSettings::execute() {
    dio.write(getInstruction());
    std::string response = dio.read();
    std::vector<std::string> v = split(response, ' ');
    std::string answer = answerToClient(v);
    updateSettings(v, answer);

}

std::vector<std::string> AlgorithSettings::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::string AlgorithSettings::validK(const std::string &s) {
    std::regex re("^[0-9]+$");
    return std::regex_match(s, re) ? "" : "invalid value for k\n";
}

std::string AlgorithSettings::validMetric(const std::string &s) {
    std::regex re("^(AUC|MAN|CHB|CAN|MIN)$");
    return std::regex_match(s, re) ? "" : "invalid value for metric\n";
}

std::string AlgorithSettings::answerToClient(std::vector<std::string> v) {
    if (v.size() != 2) {
        return "invalid input\n";
    } else {
        std::string answer;
        answer += validK(v[0]);
        answer += validMetric(v[1]);
        return answer;
    }
}

void AlgorithSettings::updateSettings(std::vector<std::string> v, std::string &answer) {
    if  (!answer.empty()) {
        knn.setK(std::stoi(v[0]));
        knn.setMetric(v[1]);
    }
    dio.write(answer);
}
