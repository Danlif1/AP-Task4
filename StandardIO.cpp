//
// Created by lenovo on 1/24/2023.
//

#include <iostream>
#include "StandardIO.h"

void StandardIO::write(std::string text) {
    std::cout << text << std::endl;
}

std::string StandardIO::read() {
    std::string temp_data;
    getline(std::cin, temp_data);
//    std::cin >> temp_data;
    return temp_data;
}
