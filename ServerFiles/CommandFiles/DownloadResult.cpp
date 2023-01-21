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
DownloadResult::DownloadResult(SocketIO &dio, KNN &knn) : Command(dio, knn) {
    description = "download results";
}

/**
 * @brief Executing the command.
 *
 */
void DownloadResult::execute() {
    if(knn.getUnclassifiedData().empty()){
        dio.write("please upload data");
    }
    std::vector<std::string> results = knn.getAllLabels();
    if(results.empty()){
        dio.write("please classify the data");
    }
    dio.write("Enter path for results file: ");
    std::string returnFile = dio.read();
    std::string filePath = "Thread" + std::to_string(pthread_self()) + returnFile;
    std::fstream writingFile(filePath,  std::ios::out | std::ios::in | std::ios::trunc);
    int lineNumber = 1;
    std::string classify;
    std::vector<std::string> labels = knn.getAllLabels();
    for (int i = 0; i < labels.size(); i++){
        std::string line = std::to_string(lineNumber) + " " + labels[i];
        writingFile << line << std::endl;
        lineNumber++;
    }
    writingFile.seekg(0, std::ios::beg);
    dio.sendFile(writingFile, SocketIO::getFileSize(returnFile));
    dio.write("Upload Complete.");
    std::remove(returnFile.data());
    std::remove(filePath.data());
    // waiting for enter.
    std::string param = dio.read();
}