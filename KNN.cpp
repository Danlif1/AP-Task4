
#include "KNN.h"

/**
 * constructor
 * Initialize KNN object and set parameters k to 5 and distance metric to Euclidean.
 */
KNN::KNN() {
    KNN::k = 5;
    KNN::distance_metric = "EUC";

}

/**
 * Constructor
 * @param k The number of neighbours we want to find.
 * @param metric The distance metric we want to use.
 */
KNN::KNN(int k, std::string metric) {
    KNN::k = k;
    KNN::distance_metric = metric;
}

////point might not need to be a class of its own, if it is it's only to separate the vector from the label
///**
// * Fits the training data to the knn object. training data consists of data(x) and labels(y).
// * @param classified_points Vector that contains classified data.
// */
//void KNN::fit(std::vector<Point> classified_points) {
//    //need to decide if we store the data as to separate arrays. might be better to utilize the class point.
//    //if we decide to not separate them we need to take care of functions in distance method.
//    KNN::classified_data = classified_points;
//}
//
//void KNN::fit_unclassified(std::vector<Point> unclassified_point) {
//    //need to decide if we store the data as to separate arrays. might be better to utilize the class point.
//    //if we decide to not separate them we need to take care of functions in distance method.
//    KNN::unclassified_data = unclassified_point;
//}

void KNN::fit_train_and_test(std::vector<Point> train, std::vector<Point> test){
    KNN::train_and_test.push_back(std::make_pair(train,test));
}

void KNN::cleanFiles(){
    train_and_test.clear();
}
/**
 * getter for k
 * @return k
 */
int KNN::getK() {
    return this->k;
}

/**
 * getter for distance metric
 * @return distance metric
 */
std::string KNN::getMetric() {
    return this->distance_metric;
}

/**
 * setter for k
 * @param k
 */

void KNN::setK(int k) {
    this->k = k;
}

/**
 * setter for distance metric
 * @param metric
 */

void KNN::setMetric(std::string metric) {
    this->distance_metric = metric;
}

/**
 */
/**
 * Predicts the label of a given unclassified vector.
 * @param newpoint The point we want to predict
 * @param place The place in the vector of tuples.
 * @return The label of the point.
 */
std::string KNN::predict(Point newpoint, int place) {
    std::vector<std::tuple<double, std::string>> dis_from_point = distance(newpoint.getAll(),place);
    std::string label = nearestNeighbor(dis_from_point);
    return label;
}

/**
 * Predicts the label of all unclassified vectors.
 * @return Vector of labels.
 */
//void KNN::predict_all() {
//    for (int i = 0; i < unclassified_data.size(); i++) {
//        all_labels.push_back(predict(unclassified_data[i]));
//    }
//}
void KNN::predict_all() {
    for (int i = 0; i < train_and_test.size(); i++) {
        for (int j = 0; j < (train_and_test[i]).second.size(); i++) {
            all_labels.push_back(predict((train_and_test[i]).second[j]),i);
        }
    }
}

/**
 * getter for all labels
 * @return all labels vector
 */
std::vector<std::string> KNN::getAllLabels() {
    return this->all_labels;
}

/**
 * Calculates the distance from the unclassified vector, to the classified data we have.
 * @param a The unclassified information.
 * @param place The place in the vector of tuples.
 * @return A vector of tuples (the tuple will consist of the distance and the classified label) with the distance of the unclassified data from the classified vector.
 */
std::vector<std::tuple<double, std::string>> KNN::distance(std::vector<double> a, int place) {
    std::vector<std::tuple<double, std::string>> dis_from_point;
    double tmp;
    for (int i = 0; i < KNN::train_and_test[place].first.size(); ++i) {
        //add calcDistance to distance file
        tmp = calcDistance(distance_metric, a, train_and_test[place].first[i].getAll());
        dis_from_point.emplace_back(tmp, train_and_test[place].first[i].getType());
    }
    return dis_from_point;
}

/**
 * Receives an array of distances and finds the max label that appears.
 * @param distances Rhe vector obtained from the distance method.
 * @return The label that appears most in the distances vector
 */
std::string KNN::nearestNeighbor(std::vector<std::tuple<double, std::string>> distances) const {
    //sort distances based on first element in ascending order
    std::sort(distances.begin(), distances.end());
    std::vector<std::string> label_of_dis;
    std::string most_common;
    for (int i = 0; i < k; ++i) {
        label_of_dis.emplace_back(std::get<1>(distances[i]));
    }
    sort(label_of_dis.begin(), label_of_dis.end());
    std::string check = label_of_dis[0];
    std::string max_label = check;
    int count = 0;
    int max = 0;
    for (int i = 0; i < label_of_dis.size(); ++i) {
        if (check == label_of_dis[i]) {
            count++;
        } else {
            if (count > max) {
                max = count;
                max_label = check;
            }
            count = 0;
            check = label_of_dis[i];
        }

    }
    return max_label;
}

std::vector<Point> KNN::getClassifiedData() {
    return this->classified_data;
}

std::vector<Point> KNN::getUnclassifiedData() {
    return this->unclassified_data;
}





