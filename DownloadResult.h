//
// Created by Daniel Lifshitz on 19/01/2023.
//

#ifndef AP_TASK4_DOWNLOADRESULT_H
#define AP_TASK4_DOWNLOADRESULT_H

#include "DefaultIO.h"
#include "Command.h"

class DownloadResult : public Command {
    void send();
public:
    DownloadResult(DefaultIO* dio, KNN* knn);
    void execute() override;
};

struct downloadThreadHelper {
    int socket_server;
    DownloadResult* downloadResult;
};

void *sendInNewSock(void *dth);


#endif //AP_TASK4_DOWNLOADRESULT_H
