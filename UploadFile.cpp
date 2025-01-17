//
// Created by Daniel Lifshitz on 18/01/2023.
//

#include "UploadFile.h"
#include "SafetyChecks.h"

UploadFile::UploadFile(DefaultIO *dio, KNN *knn) {
    this->dio = dio;
    this->knn = knn;
    this->description = "1. upload an unclassified csv file\n";
    this->instruction = "Please upload your local train CSV file.";
    this->insturction_2 = "Please upload your local test CSV file.";
}

bool UploadFile::isFileGood(std::vector<Point> input) {
    std::cout << "isFileGood" << std::endl;
    if (!input.empty() && IsSameSize(input)) {
        return true;
    } else {
        return false;
    }
}

std::vector<Point> UploadFile::getClassifiedFromClient() {
    std::vector<Point> data;
    std::string line = dio->read();
    if (line == "file not found") {
        return data;
    }
    std::vector<std::string> elems;
    while (line != "$") {
        elems.clear();
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
    if (line == "file not found") {
        return data;
    }
    while (line != "$") {
        Point p;
        p.setFromString(line, ',');
        data.push_back(p);
        line = dio->read();
    }
    return data;
}

void UploadFile::execute() {
    dio->write(instruction);
    dio->write("$");
    std::vector<Point> classifiedPoints = getClassifiedFromClient();
    if (!isFileGood(classifiedPoints)) {
        dio->write("invalid input.\n");
        return;
    } else {
        knn->fit(classifiedPoints);
        dio->write("Upload complete.\n");
        dio->write(insturction_2);
        dio->write("$");
        std::vector<Point> unclassifiedPoints = getUnclassifiedFromClient();
        if (isFileGood(unclassifiedPoints) &&
            unclassifiedPoints[0].getAll().size() == classifiedPoints[0].getAll().size()) {
            knn->fit_unclassified(unclassifiedPoints);
            dio->write("Upload complete.");
            dio->write("$");
            return;
        } else {
            dio->write("invalid input.$");
            return;
        }
    }


}


