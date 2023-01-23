//
// Created by Daniel Lifshitz on 23/01/2023.
//

#ifndef AP_TASK4_SERVERTIMER_H
#define AP_TASK4_SERVERTIMER_H


#include <atomic>
#include "../SocketFiles/SocketFile.h"

extern pthread_mutex_t mutex;
extern pthread_cond_t condition;
class ServerTimer {
private:
    pthread_t t1{};
    pthread_attr_t attr{};
    SocketFile& SFS;
    int seconds = 60;
public:
    ServerTimer(SocketFile& SFS);
    static void* accept(void* obj);
    bool start(int&cs);

    int getSeconds() const;
};


#endif //AP_TASK4_SERVERTIMER_H
