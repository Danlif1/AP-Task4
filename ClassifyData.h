//
// Created by lenovo on 1/17/2023.
//

#ifndef AP_4_CLASSIFYDATA_H
#define AP_4_CLASSIFYDATA_H


#include "Command.h"

class ClassifyData : public Command {
public:
    ClassifyData(DefaultIO &dio, KNN &knn) : Command(dio, knn) {
        description = "3. classify data\n";
        instruction = "";
    };
    void execute() override;
};


#endif //AP_4_CLASSIFYDATA_H
