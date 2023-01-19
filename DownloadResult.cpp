//
// Created by Daniel Lifshitz on 19/01/2023.
//

#include <iostream>
#include <fstream>
#include "DownloadResult.h"
#include "DefaultIO.h"
#include "SocketIO.h"
#include "StandardIO.h"

/**
 * @brief Construct a new Download Result:: Download Result object.
 *
 * @param dio DefaultIO used.
 * @param knn The knn class used.
 */
DownloadResult::DownloadResult(DefaultIO &dio, KNN &knn) : Command(dio, knn) {
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
    defaultIo.write("Enter path for results file: ");
    std::string returnFile = dio.read();
    std::fstream readingFile(returnFile, std::ios::in);
    std::string results_path =  "Thread" + std::to_string(pthread_self());
    std::fstream writingFile(results_path,  std::ios::out | std::ios::in | std::ios::trunc);
    int lineNumber = 1;
    std::string classify;
    while (getline(readingFile, classify)) {
        std::string line = std::to_string(lineNumber) + " " + classify;
        writingFile << line << std::endl;
        lineNumber++;
    }
    writingFile.seekg(0, std::ios::beg);
    defaultIo.sendFile(writingFile, SocketIO::getFileSize(results_path));
    defaultIo.write("Upload Complete.");
    std::remove(results_path.data());
    // waiting for enter.
    std::string param = defaultIo.read();
}