//
// Created by lenovo on 1/24/2023.
//

#ifndef UNTITLED1_STANDARDIO_H
#define UNTITLED1_STANDARDIO_H
#include "DefaultIO.h"

class StandardIO : public DefaultIO {
public:
    std::string input;

    StandardIO() = default;

    void write(std::string text) override;

    std::string read() override;
};


#endif //UNTITLED1_STANDARDIO_H
