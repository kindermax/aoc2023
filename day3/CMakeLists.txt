cmake_minimum_required(VERSION 3.26)

project(day3 C)

set(CMAKE_C_STANDARD 17)

set(SOURCE_FILES main.c)

add_executable(day3 ${SOURCE_FILES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)