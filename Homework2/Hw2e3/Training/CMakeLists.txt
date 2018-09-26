cmake_minimum_required(VERSION 3.10)
project(Training)

set(CMAKE_CXX_STANDARD 14)

add_executable(Training main.cpp DataSet.cpp DataSet.h Network.cpp Network.h Misc.cpp Misc.h)
