//
// Created by Daniel Lifshitz on 23/01/2023.
//

#ifndef AP_TASK4_THREADCLI_H
#define AP_TASK4_THREADCLI_H


#include <pthread.h>
#include "CLI.h"

class ThreadCLI {
private:
    pthread_t _thread;
    pthread_attr_t attr;
    bool valid{};
    static void* start_function(void* obj);
    CLI cli;
    DefaultIO& dio;
public:
    ThreadCLI( DefaultIO& dio, KNN& knn);
    bool start_thread();
    void wait_for_thread_to_exit() const;
    ~ThreadCLI();
};



#endif //AP_TASK4_THREADCLI_H
