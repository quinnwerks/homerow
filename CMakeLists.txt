# blah
# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)
# Project's name
project(homerow)
# Using C++ 14
set(CMAKE_CXX_STANDARD 14)

include_directories(src)
# .-lib
# |
# |-src
# \
#  -tst
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)
