//
// Created by lenovo on 1/24/2023.
//

#ifndef UNTITLED1_DEFAULTIO_H
#define UNTITLED1_DEFAULTIO_H

#include <string>


class DefaultIO {
public:
    virtual std::string read() = 0;

    virtual void write(std::string text) = 0;

    virtual ~DefaultIO() = default;
};


#endif //UNTITLED1_DEFAULTIO_H
