cmake_minimum_required(VERSION 3.6)
project(expertSystem)

set(CMAKE_CXX_STANDARD 11)

include_directories(headers)

set(SOURCE_FILES
    srcs/main.cpp
    srcs/Node.class.cpp
    srcs/ParsedNode.class.cpp
    srcs/Parser.class.cpp
    srcs/Lexer.class.cpp
    headers/Lexer.class.hpp
    headers/Parser.class.hpp
    headers/ParsedNode.class.hpp
    headers/Node.class.hpp
    )

add_executable(expertSystem ${SOURCE_FILES})