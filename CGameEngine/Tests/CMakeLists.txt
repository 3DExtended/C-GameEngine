include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

message(${CMAKE_CXX_FLAGS})

add_executable (tests Main.cpp)
target_link_libraries (tests LINK_PUBLIC engine)

enable_testing()
add_test( AllTests tests )