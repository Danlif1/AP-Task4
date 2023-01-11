//
// Created by lenovo on 1/11/2023.
//

#ifndef AP_4_SOCKETIO_H
#define AP_4_SOCKETIO_H


#include "DefaultIO.h"

class SocketIO: public DefaultIO {
    void write(double d) override;
    void write(std::string text) override;
    std::string read() override;
};




#endif //AP_4_SOCKETIO_H
