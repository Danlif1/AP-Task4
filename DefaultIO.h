//
// Created by lenovo on 1/11/2023.
//

#ifndef AP_TASK4_DEFAULTIO_H
#define AP_TASK4_DEFAULTIO_H


#include <string>

class DefaultIO {
public:
    virtual std::string read() = 0;
    virtual void write(std::string text) = 0;
    virtual void sendFile(std::fstream& file_s, long file_size) = 0; //full file stream
    
    virtual void write(double d)=0;
    virtual ~DefaultIO()= default;
    };


#endif //AP_TASK4_DEFAULTIO_H
