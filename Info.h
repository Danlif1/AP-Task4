//
// Created by Daniel Lifshitz on 14/01/2023.
//

#ifndef AP_TASK4_INFO_H
#define AP_TASK4_INFO_H


#include <string>

class Info {
private:
    int k;
    std::string distMetric;
    std::string path_to_train;
    std::string path_to_test;
    std::string classify_file_name;
public:
    // Getters.
    int getK() const;

    const std::string &getDistanceMetric() const;

    const std::string &getPathToTrain() const;

    const std::string &getPathToTest() const;

    std::string &getClassifyName();

    // Setters.
    void setK(int k);

    void setDistanceMetric(const std::string &distanceMetric);

    void setPathToTrain(const std::string &pathToTrain);

    void setPathToTest(const std::string &pathToTest);

    void setClassifyName(std::string &classifiedName);
};


#endif //AP_TASK4_INFO_H
