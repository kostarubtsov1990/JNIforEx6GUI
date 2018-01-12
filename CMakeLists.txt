cmake_minimum_required(VERSION 3.8)
project(JNIforEx6GUI)

set(CMAKE_BUILD_TYPE Release)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES sample_DefaultReversiGameLogic.h sample_DefaultReversiGameLogic.cpp include/Board.h src/Board.cpp
        include/GameLogic.h src/GameLogic.cpp include/DefaultLogic.h src/DefaultLogic.cpp include/Cell.h src/Cell.cpp)
add_library(JNIforEx6GUI SHARED ${SOURCE_FILES})