cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)

project(Gizmo)

add_library(compiler STATIC
        compiler/gizCompiler.cpp
        compiler/gizCompiler.h
        compiler/lexer.cpp
        compiler/lexer.h
        compiler/parser.cpp
        compiler/parser.h
        compiler/codeGenerator.cpp
        compiler/codeGenerator.h
)

add_executable(Gizmo main.cpp)

target_link_libraries(Gizmo compiler)