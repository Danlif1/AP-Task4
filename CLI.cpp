//
// Created by lenovo on 1/17/2023.
//

#include "CLI.h"
#include <regex>
CLI::CLI(DefaultIO* dio, KNN* knn){
this->dio = dio;
this->knn = knn;
commands.insert({1, new UploadFile(dio, knn)});
commands.insert({2, new AlgorithmSettings(dio, knn)});
commands.insert({3, new ClassifyData(dio, knn)});
commands.insert({4, new DisplayResult(dio, knn)});
commands.insert({5, new DownloadResult(dio, knn)});
should_continue = true;
}



void CLI::start() {
    while (should_continue) {
        printMenu();
        waitForInput();
        std::cout<< "finished command" << std::endl;
    }
}


void CLI::printMenu() {
    std::string response = "Welcome to the KNN Classifier Server. Please choose an option.\n";
    for (int i = 0; i < commands.size(); ++i) {
        response += commands[i + 1]->description;
    }
    response += "8. exit";
    dio->write(response);
    dio->write("$");
    std::cout << "done" << std::endl;
}

void CLI::waitForInput() {
    std::string input = dio->read();
    std::cout << "input: " << input << std::endl;

    if (input == "8"){
        should_continue = false;
    } else if (isValidInput(input)) {
        int index = std::stoi(input);
        commands[index]->execute();
    } else {
        dio->write("Invalid input\n");
    }
}

bool CLI::isValidInput(std::string input) {
    std::regex re("^(1|2|3|4|5)$");
    return std::regex_match(input, re);
}
