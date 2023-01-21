//
// Created by lenovo on 1/11/2023.
//

#ifndef AP_4_STANDARDIO_H
#define AP_4_STANDARDIO_H


#include "DefaultIO.h"

class StandardIO : public DefaultIO {
    std::string input;

    void write(double d) override;

    void write(std::string text) override;

    //void sendFile(std::fstream& file_s, long file_size);

    std::string read() override;
};


#endif //AP_4_STANDARDIO_H
