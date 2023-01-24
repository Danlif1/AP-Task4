//
// Created by Daniel Lifshitz on 18/01/2023.
//

#include "DisplayResult.h"

DisplayResult::DisplayResult(DefaultIO* dio, KNN* knn){
    description = "4. display results\n";
    this->dio = dio;
    this->knn = knn;
}

void DisplayResult::execute() {
    if (knn->getUnclassifiedData().empty()){
        dio->write("please upload data");
        return;
    } else if(knn->getAllLabels().empty()) {
        dio->write("please classify the data");
        return;
    }
    for (int i = 0; i < knn->getAllLabels().size(); i++){
        int place = i+1;
        std::string result = std::to_string(place) + "\t" + knn->getAllLabels()[i] + "\n";
        dio->write(result);
    }
    dio->write("Done.");
    do {} while (dio->read() != "\n");
}
