
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

    std::vector<std::tuple<double, std::string>> distance(std::vector<double> a);
    std::string nearestNeighbor(std::vector<std::tuple<double, std::string>> distances) const;


public:
    KNN();

    KNN(int k, std::string metric);

    int getK();

    std::string getMetric();

    void setK(int k);

    void setMetric(std::string metric);

    void fit(std::vector<Point> classified_point);

    std::vector<Point> getClassifiedData();

    std::vector<Point> getUnclassifiedData();

    void fit_unclassified(std::vector<Point> unclassified_point);

    std::string predict(Point newpoint);

    void predict_all();

    std::vector<std::string> getAllLabels();

    void cleanResults();
};

#endif //AP_TASK3_KNN_H