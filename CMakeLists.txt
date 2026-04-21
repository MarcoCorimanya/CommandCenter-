cmake_minimum_required(VERSION 4.0)
project(CommandCenter)

set(CMAKE_CXX_STANDARD 20)

add_executable(CommandCenter main.cpp
        Entity.hpp
        Entity.cpp
        CommandCenter.cpp
        CommandCenter.hpp)
