include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable (tests Main.cpp)
target_link_libraries (tests LINK_PUBLIC engine)