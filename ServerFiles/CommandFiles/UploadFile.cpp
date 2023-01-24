//
// Created by Daniel Lifshitz on 18/01/2023.
//

#include "UploadFile.h"

const std::string &UploadFile::getInstruction(int part){
    switch (part){
        case 1:
            return instruction;
        case 2:
            return insturction2;
    }
    // We won't get here, but we use this to remove the warning.
    return instruction;
}


void UploadFile::execute() {
    dio.write(getInstruction(1));
    std::string response = dio.read();
    std::fstream fout;
    if (!CheckFile(response)) {
        //The file doesn't end with .csv, so we need to terminate the program.
        dio.write("invalid input");
        return;
    } else {
        // Opening the file.
        fout.open(response, std::ios::out | std::ios::app);
    }
    PointReader classifiedPointReader(response);
    Point cPoint;
    std::vector<Point> classifiedPoints;
    //creating an array of classified points.
    while (classifiedPointReader.getNextPoint(cPoint)) { classifiedPoints.push_back(cPoint); }
    dio.write("Upload complete.");
    dio.write(getInstruction(2));
    std::string response2 = dio.read();
    if (!CheckFile(response2)) {
        //The file doesn't end with .csv, so we need to terminate the program.
        dio.write("invalid input");
        return;
    } else {
        // Opening the file.
        fout.open(response2, std::ios::out | std::ios::app);
    }
    PointReader unclassifiedPointReader(response2);
    Point ucPoint;
    std::vector<Point> unclassifiedPoints;
    //creating an array of classified points.
    while (unclassifiedPointReader.getNextPoint(ucPoint)) { unclassifiedPoints.push_back(ucPoint); }

    // we don't want to save the previous unclassified file with the new classified file by mistake.
    knn.fit(classifiedPoints);
    knn.fit_unclassified(unclassifiedPoints);
    dio.write("Upload complete.");

}


