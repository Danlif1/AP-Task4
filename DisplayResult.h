//
// Created by Daniel Lifshitz on 18/01/2023.
//

#ifndef AP_TASK4_DISPLAYRESULT_H
#define AP_TASK4_DISPLAYRESULT_H

#include "Command.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "PointReader.h"

class DisplayResult : public Command {
public:
    DisplayResult(DefaultIO &dio, KNN &knn) : Command(dio, knn) {
        description = "4. display results\n";
    };
    void execute() override;
};


#endif //AP_TASK4_DISPLAYRESULT_H
