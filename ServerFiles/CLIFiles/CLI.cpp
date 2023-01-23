//
// Created by lenovo on 1/17/2023.
//

#include "CLI.h"
#include <regex>

void CLI::start() {
    while (true) {
        printMenu();
        waitForInput();
    }

}


void CLI::printMenu() {
    std::string response = "Welcome to the KNN Classifier Server. Please choose an option.\n";
    for (int i = 0; i < commands.size(); ++i) {
        response += commands[i]->getDescription();
    }
    dio.write(response);
}

void CLI::waitForInput() {
    std::string input = dio.read();
    if (isValidInput(input)) {
        int index = std::stoi(input);
        commands[index]->execute();
    } else {
        dio.write("Invalid input");
    }
}

bool CLI::isValidInput(std::string input) {
    std::regex re("^(1|2|3|4|5|8)$");
    return std::regex_match(input, re);
}
