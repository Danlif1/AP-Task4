#include <regex>
#include <iostream>
#include "KNN.h"
#include "AlgorithmSettings.h"
#include "SocketIO.h"
#include "StandardIO.h"
//#include "CLI.h"
#include "ClassifyData.h"



int main() {
KNN* knn = new KNN();
//SocketIO* socketIo = new SocketIO(1);
StandardIO* standardIo = new StandardIO();
AlgorithmSettings* algorithmSettings = new AlgorithmSettings(standardIo, knn);
ClassifyData* classifyData = new ClassifyData(standardIo, knn);

while (true) {
    algorithmSettings->execute();
//    classifyData->execute();

}

    return 0;
}

