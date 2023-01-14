//
// Created by Daniel Lifshitz on 14/01/2023.
//

#include "Info.h"

/**
 * @brief Getter for k.
 * 
 * @return int The k used in KNN algorithm.
 */
int Info::getK() const {
    return k;
}

/**
 * @brief Setter for k.
 * 
 * @param k The k used in KNN algorithm.
 */
void Info::setK(int k) {
    Info::k = k;
}

/**
 * @brief Getter for the distance metric.
 * 
 * @return const std::string& The distance metric used in KNN algorithm.
 */
const std::string &Info::getDistanceMetric() const {
    return distMetric;
}

/**
 * @brief Setter for the distance metric.
 * 
 * @param distanceMetric The distance metric used in knn algorithm.
 */
void Info::setDistanceMetric(const std::string &distanceMetric) {
    distMetric = distanceMetric;
}

/**
 * @brief Getter for the path for the train file.
 * 
 * @return const std::string& The path to the train file.
 */
const std::string &Info::getPathToTrain() const {
    return path_to_train;
}

/**
 * @brief Setter for the path for the train file.
 * 
 * @param pathToTrain The path to the train file.
 */
void Info::setPathToTrain(const std::string &pathToTrain) {
    path_to_train = pathToTrain;
}

/**
 * @brief Getter for the path for the test file.
 * 
 * @return const std::string& The path to the test file.
 */
const std::string &Info::getPathToTest() const {
    return path_to_test;
}

/**
 * @brief Setter for the path for the test file.
 * 
 * @param pathToTest The path to the test file.
 */
void Info::setPathToTest(const std::string &pathToTest) {
    path_to_test = pathToTest;
}

/**
 * @brief Getter for the name of the classified file.
 * 
 * @return std::string& The name of the classified file.
 */
std::string &Info::getClassifyName() {
    return classify_file_name;
}

/**
 * @brief Setter for the name of the classified file.
 * 
 * @param classifiedName The name of the classified file.
 */
void Info::setClassifyName(std::string &classifiedName){
    classify_file_name = classifiedName;
}
