cmake_minimum_required(VERSION 3.12)
project(Training)

set(CMAKE_CXX_STANDARD 14)

add_executable(Training main.cpp TrainingSet.cpp TrainingSet.h Network.cpp Network.h)