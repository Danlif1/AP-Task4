//
// Created by lenovo on 1/11/2023.
//

#ifndef AP_4_STANDARDIO_H
#define AP_4_STANDARDIO_H


#include "DefaultIO.h"

class StandardIO : public DefaultIO {
public:
    std::string input;

    StandardIO() = default;

    void write(double d) override;

    void write(std::string text) override;

    std::string read() override;
};


#endif //AP_4_STANDARDIO_H
