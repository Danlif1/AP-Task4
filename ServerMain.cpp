// Server side C/C++ program to demonstrate Socket
// programming
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Server.h"

void* multiClient(void *info) {
    Server* server = (Server*) info;
    server->connectToClient();
    pthread_exit(NULL);
}
/**
 * @brief The main function of the server
 * 
 * @param argc Should have file and port by that order.
 * @param argv Should be 3.
 * @return int Returning 0 if there is a problem with the inputs.
 */
int main(int argc, char const* argv[]) {
    Server server = Server(atoi(argv[1]));
    // We will be able to support 5 clients at the same time.
    while(true){
        pthread_t threads[5];
        for(int i = 0; i < 5; i++){
            pthread_create(&threads[i], NULL, multiClient, (void *)&server);
        }
    }
    server.closeSocket();
    delete &server;
    return 0;
}
