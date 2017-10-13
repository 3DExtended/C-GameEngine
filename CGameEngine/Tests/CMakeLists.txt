# Add executable called "tests" that is built from the source files
# "Main.cpp".

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/include)

echo ("Tests")
add_executable (tests Main.cpp)
target_link_libraries (tests LINK_PUBLIC engine)