cmake_minimum_required(VERSION 3.28)
project(Gizmo)

set(CMAKE_CXX_STANDARD 20)

add_executable(Gizmo main.cpp
        lexer.cpp
        lexer.h
)
