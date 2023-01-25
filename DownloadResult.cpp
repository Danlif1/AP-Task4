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
DownloadResult::DownloadResult(DefaultIO *dio, KNN *knn) {
    description = "5. download results\n";
    this->dio = dio;
    this->knn = knn;
}

void DownloadResult::send() {
    for (int i = 0; i < knn->getAllLabels().size(); i++) {
        int place = i + 1;
        std::string result = std::to_string(place) + "\t" + knn->getAllLabels()[i] + "\n";
        dio->write(result);
    }
    dio->write("$");
}


/**
 * @brief Executing the command.
 *
 */
void DownloadResult::execute() {
    if (knn->getUnclassifiedData().empty()) {
        dio->write("-");
        dio->write("please upload data");
        dio->write("$");
        return;
    } else if (knn->getAllLabels().empty()) {
        dio->write("-");
        dio->write("please classify the data");
        dio->write("$");
        return;
    } else {
        dio->write("*");
        dio->write("Please enter file path");
        dio->write("$");
        if (dio->read() == "valid") {
            //TODO: create thread to handle the download
            send();
        }
    }

}