cmake_minimum_required(VERSION 3.25)

project(untitled1)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(untitled1 main.cpp
        StandardIO.h
        StandardIO.cpp
        CalcDist.cpp
        CalcDist.h
        KNN.cpp
        KNN.h
        Point.cpp
        SocketIO.cpp
        Command.h
        AlgorithmSettings.h
        SafetyChecks.cpp
        SafetyChecks.h
        AlgorithmSettings.cpp
        ClassifyData.cpp
        ClassifyData.h
        DisplayResult.cpp
        DisplayResult.h
        UploadFile.cpp
        UploadFile.h
        DownloadResult.cpp
        CLI.cpp
        CLI.h)
