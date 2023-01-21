//
// Created by lenovo on 1/17/2023.
//

#include "ClassifyData.h"

void ClassifyData::execute() {
    if (knn.getClassifiedData().empty() || knn.getUnclassifiedData().empty()) {
        dio.write("Please upload data\n");
    } else {
        knn.predict_all();
        dio.write("classifying data complete\n");
    }
}
