//
// Created by lenovo on 1/11/2023.
//

#include <iostream>
#include "StandardIO.h"

void StandardIO::write(std::string text) {
    std::cout << text << std::endl;
}

std::string StandardIO::read() {
    getline(std::cin, this->input);
    return input;
}
