cmake_minimum_required(VERSION 3.6)
project(expertSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(headers)

set(SOURCE_FILES
    headers/Lexer.class.hpp
    headers/Node.class.hpp
    headers/ParsedNode.class.hpp
    headers/Parser.class.hpp
    headers/Fact.class.hpp
    headers/Rule.class.hpp
    headers/RuleBase.class.hpp
    headers/FactBase.class.hpp
    headers/Motor.class.hpp
    headers/IObject.hpp
    headers/Operand.class.hpp
    srcs/Lexer.class.cpp
    srcs/main.cpp
    srcs/Node.class.cpp
    srcs/ParsedNode.class.cpp
    srcs/Parser.class.cpp
    srcs/Fact.class.cpp
    srcs/Rule.class.cpp
    srcs/FactBase.class.cpp
    srcs/RuleBase.class.cpp
    srcs/Motor.class.cpp
    srcs/Operand.class.cpp
    CMakeLists.txt
    Makefile
    test1.txt
    test2.txt)

add_executable(expertSystem ${SOURCE_FILES})