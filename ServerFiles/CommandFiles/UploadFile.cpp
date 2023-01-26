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
    // sending the instructions.
    dio.write(getInstruction(1));
    std::string response = dio.read();
    bool emp = response.empty();
    char space = ' ';
    // Checking the file.
    if (!CheckFile(response)) {
        //The file doesn't end with .csv, so we need to terminate the program.
        dio.write("invalid input");
        return;
    } else {
        dio.write("");
    }

    std::vector<Point> classifiedPoints;
    // Reading the file.
    while(!emp){
        Point cPoint;
        cPoint.setFromString(response, space);
        classifiedPoints.push_back(cPoint);
        response = dio.read();
        emp = response.empty();
    }
    // Sending Upload complete.
    dio.write("Upload complete.");

    // Sending another instruction.
    dio.write(getInstruction(2));
    // Reading the file path.
    std::string response2 = dio.read();
    emp = response2.empty();
    if (!CheckFile(response2)) {
        //The file doesn't end with .csv, so we need to terminate the program.
        dio.write("invalid input");
        return;
    }

    std::vector<Point> unclassifiedPoints;
    // Reading the file.
    while(!emp){
        Point ucPoint;
        ucPoint.setFromString(response2, ' ');
        unclassifiedPoints.push_back(ucPoint);
        response2 = dio.read();
        emp = response2.empty();
    }
    // we don't want to save the previous unclassified file with the new classified file by mistake.
    knn.fit(classifiedPoints);
    knn.fit_unclassified(unclassifiedPoints);
    // Sending Upload complete.
    dio.write("Upload complete.");

}


