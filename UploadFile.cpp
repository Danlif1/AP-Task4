//
// Created by Daniel Lifshitz on 18/01/2023.
//

#include "UploadFile.h"

const std::string &UploadFile::getInstruction(int part){
    switch (part){
        case 1:
            return instruction;
        case 2:
            return instruction2;

    }
}


void UploadFile::execute() {
    dio.write(getInstruction(1));
    std::string response = dio.read();
    if (!CheckFile(fileName)) {
        //The file doesn't end with .csv, so we need to terminate the program.
        dio.write("invalid input")
        return 0;
    } else {
        // Opening the file.
        fout.open(response, std::ios::out | std::ios::app);
    }
    PointReader classifiedPointReader(response);
    Point cPoint;
    std::vector<Point> classifiedPoints;
    //creating an array of classified points.
    while (classifiedPointReader.getNextPoint(cPoint)) { classifiedPoints.push_back(cPoint); }
    dio.write("Upload complete.")
    dio.write(getInstruction(2));
    std::string response2 = dio.read();
    if (!CheckFile(response2)) {
        //The file doesn't end with .csv, so we need to terminate the program.
        dio.write("invalid input")
        return 0;
    } else {
        // Opening the file.
        fout.open(response2, std::ios::out | std::ios::app);
    }
    PointReader unclassifiedPointReader(response2);
    Point ucPoint;
    std::vector<Point> unclassifiedPoints;
    //creating an array of classified points.
    while (unclassifiedPointReader.getNextPoint(ucPoint)) { unclassifiedPoints.push_back(ucPoint); }
    knn.fit_train_and_test(classifiedPoints,unclassifiedPoints);
    dio.write("Upload complete.")

}


