// Server side C/C++ program to demonstrate Socket
// programming


#include "CLIFiles/CLI.h"
#include "CLIFiles/ThreadCLI.h"
#include "ServerTimer.h"
#include "../SocketFiles/SocketFile.h"
#include "../SocketFiles/SocketIO.h"


/**
 * @brief Removing inactive sockets.
 *
 * @param vSIO Vector of socketIO pointers.
 */
void remove_inactive_sockets(std::vector<SocketIO*>& vSIO) {
    for(int j = 0; j<vSIO.size();j++) {
        SocketIO* s = vSIO.at(j);
        if(!s->is_active()) {
            delete s;
            vSIO.erase(vSIO.begin()+j);
            j-=1;
        }
    }
}

/**
 * @brief The main function of the server
 * 
 * @param argc Should have file and port by that order.
 * @param argv Should be 3.
 * @return int Returning 0 if there is a problem with the inputs.
 */
int main(int argc, char const* argv[]) {
    if (argc != 2) {
        std::cout << "Please enter port." << std::endl;
        return 0;
    }
    int port = std::stoi(argv[1]);
    SocketFile SFS(port);
    std::vector <ThreadCLI*> thread_vector;
    std::vector <SocketIO*> vSIO;
    bool resume_server = true;
    while (true) { //need to do server timeout.
        remove_inactive_sockets(vSIO);
        ServerTimer serverTimer(SFS);
        int client_sock;
        resume_server = serverTimer.start(client_sock);
        while (!vSIO.empty() && !resume_server) {
            remove_inactive_sockets(vSIO);
            resume_server = serverTimer.start(client_sock);
        }
        SocketIO *socketIo = new SocketIO(client_sock);
        vSIO.push_back(socketIo);
        KNN* knn = new KNN();
        ThreadCLI *t_CLI = new ThreadCLI(*socketIo, *knn);
        thread_vector.push_back(t_CLI);
        t_CLI->start_thread();
    }
    for (ThreadCLI *t: thread_vector) {
        delete t;
    }
    for (SocketIO *s: vSIO) {
        delete s;
    }
}
