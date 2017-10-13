include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable (tests Main.cpp EngineTester.cpp)
target_link_libraries (tests ${CMAKE_CURRENT_SOURCE_DIR}/../src/libengine.a)