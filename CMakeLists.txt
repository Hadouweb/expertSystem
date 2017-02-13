cmake_minimum_required(VERSION 3.6)
project(expertSystem)

set(CMAKE_CXX_STANDARD 11)

include_directories(headers)

set(SOURCE_FILES
    srcs/main.cpp
    )

add_executable(expertSystem ${SOURCE_FILES})