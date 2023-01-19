//
// Created by Daniel Lifshitz on 18/01/2023.
//

#include "DisplayResult.h"

void DisplayResult::execute() {
    if (knn.isTrainEmpty()){
        dio.write("please upload data");
    } else if(knn.getAllLabels().empty()) {
        dio.write("please classify the data");
    }
    std::string response = dio.read();
    for (int i = 0; i < knn.getAllLabels().size(); i++){
        int place = i+1;
        std::string result = to_string(place) + " " + knn.getAllLabels()[i];
        dio.write(result);
    }
    knn.cleanResults();
    dio.write("Done.");
}
