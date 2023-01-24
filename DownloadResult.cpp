//
// Created by Daniel Lifshitz on 19/01/2023.
//

#include <iostream>
#include <fstream>
#include "DownloadResult.h"


/**
 * @brief Construct a new Download Result:: Download Result object.
 *
 * @param dio DefaultIO used.
 * @param knn The knn class used.
 */
DownloadResult::DownloadResult(DefaultIO* dio, KNN* knn) {
    description = "5. download results\n";
    this->dio = dio;
    this->knn = knn;
}

/**
 * @brief Executing the command.
 *
 */
void DownloadResult::execute() {
    if (knn->getUnclassifiedData().empty()){
        dio->write("please upload data");
        return;
    } else if(knn->getAllLabels().empty()) {
        dio->write("please classify the data");
        return;
    }
    for (int i = 0; i < knn->getAllLabels().size(); i++){
        int place = i+1;
        std::string result = std::to_string(place) + "\t" + knn->getAllLabels()[i];
        dio->write(result);
    }
    do {} while (dio->read() != "\n");
}