//
// Created by lenovo on 1/17/2023.
//

#include "ClassifyData.h"

ClassifyData::ClassifyData(DefaultIO* dio, KNN* knn) {
    description = "3. classify data\n";
    instruction = "";
    this->dio = dio;
    this->knn = knn;
};

void ClassifyData::execute() {
    std::cout << "classify data" << std::endl;
    if (knn->getClassifiedData().empty() || knn->getUnclassifiedData().empty()){
        dio->write("please upload data\n$");
    } else {
        knn->predict_all();
        dio->write("classifying data complete\n$");
    }
}
