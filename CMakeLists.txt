# cmake_minimum_required(VERSION <specify CMake version here>)
project(Thread)

set(CMAKE_CXX_STANDARD 14)

add_executable(Thread main.cpp ThreadTest.c student.h Foorbarprint.c)