//
// Created by Daniel Lifshitz on 18/01/2023.
//

#include "UploadFile.h"
#include "SafetyChecks.h"

UploadFile::UploadFile(DefaultIO* dio, KNN* knn) {
    description = "1. upload an unclassified csv file\n";
    instruction = "Please upload your local train CSV file.";
    insturction_2 = "Please upload your local test CSV file.";
}

bool UploadFile::isFileGood(std::vector<Point> input) {
    if(IsSameSize(input) && !input.empty()){
        return true;
    } else {
        return false;
    }
}

std::vector<Point> UploadFile::getClassifiedFromClient() {
    std::vector<Point> data;
    std::string word;
    std::vector<std::string> elems;
    std::string line = dio->read();
    while (line != "$") {
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ',')) {
            elems.push_back(item);
        }
        Point p;
        p.setFromVector(elems);
        data.push_back(p);
        line = dio->read();
    }
    return data;
}

std::vector<Point> UploadFile::getUnclassifiedFromClient() {
    std::string line = dio->read();
    std::vector<Point> data;
    while (line != "$") {
        Point p;
        p.setFromString(line, ',');
        data.push_back(p);
        line = dio->read();
    }
    return data;
}

void UploadFile::execute() {
    dio->write(this->instruction);
    std::vector<Point> classifiedPoints = getClassifiedFromClient();
    if(!isFileGood(classifiedPoints)){
        dio->write("invalid input.");
        return;
    } else {
        knn->fit(classifiedPoints);
        dio->write("Upload complete.");
        dio->write(this->insturction_2);
        std::vector<Point> unclassifiedPoints = getUnclassifiedFromClient();
        if (isFileGood(unclassifiedPoints) &&
        unclassifiedPoints[0].getAll().size() == classifiedPoints[0].getAll().size()) {
            knn->fit_unclassified(unclassifiedPoints);
            dio->write("Upload complete.");
            return;
        } else {
            dio->write("invalid input.");
            return;
        }
    }


}


