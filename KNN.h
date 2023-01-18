
#ifndef AP_TASK3_KNN_H
#define AP_TASK3_KNN_H

#include <tuple>
#include <algorithm>
#include "CalcDist.h"


class KNN {
    int k;
    std::string distance_metric;
    std::vector<Point> classified_data;
    std::vector<Point> unclassified_data;
    std::vector<std::string> all_labels;

    // We have a vector that holds the train files and the test files in a tuple.
    std::vector<std::pair<std::vector<Point>,std::vector<Point>>> train_and_test;
    std::vector<std::tuple<double, std::string>> distance(std::vector<double> a);
    std::string nearestNeighbor(std::vector<std::tuple<double, std::string>> distances) const;


public:
    KNN();

    KNN(int k, std::string metric);

    int getK();

    std::string getMetric();

    void setK(int k);

    void setMetric(std::string metric);

//    void fit(std::vector<Point> classified_point);

    std::vector<Point> getClassifiedData();

    std::vector<Point> getUnclassifiedData();

//    void fit_unclassified(std::vector<Point> unclassified_point);

    void fit_train_and_test(std::vector<Point> train, std::vector<Point> test);

    void cleanFiles();

    std::string predict(Point newpoint);

    void predict_all();

    bool isTrainEmpty(){
        if(train_and_test.empty()){
            return true;
        } else {
            return false;
        }
    }
    std::vector<std::string> getAllLabels();
};

#endif //AP_TASK3_KNN_H
