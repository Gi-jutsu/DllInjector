cmake_minimum_required(VERSION 3.15)
project(DllInjector)

set(CMAKE_CXX_STANDARD 14)

add_executable(DllInjector src/main.cpp src/DllInjector/DllInjector.cpp src/DllInjector/DllInjector.h)