PROJECT (engine C CXX)
cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_FLAGS "-std=c++17 $(CMAKE_CXX_FLAGS)")

ADD_SUBDIRECTORY( src )
