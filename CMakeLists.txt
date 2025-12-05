cmake_minimum_required(VERSION 3.10)
project(MyProgram LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

add_executable(main src/main.cpp)
add_executable(test tests/TestCase.cpp)