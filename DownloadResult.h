//
// Created by Daniel Lifshitz on 19/01/2023.
//

#ifndef AP_TASK4_DOWNLOADRESULT_H
#define AP_TASK4_DOWNLOADRESULT_H

#include "DefaultIO.h"
#include "Command.h"

class DownloadResult : public Command {
public:
    DownloadResult(DefaultIO* dio, KNN* knn);
    void execute() override;
};



#endif //AP_TASK4_DOWNLOADRESULT_H
