cmake_minimum_required(VERSION 3.9)

set(CMAKE_BUILD_TYPE Release)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/Util)

add_library(engine STATIC Engine/Util/main.cpp)

target_link_libraries(engine lib)