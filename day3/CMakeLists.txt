cmake_minimum_required(VERSION 3.26)

project(day3 C)

set(CMAKE_C_STANDARD 17)

set(SOURCE_FILES main.c)
set(RESOURCE_FILES input.txt input_test.txt)

add_executable("${PROJECT_NAME}" ${SOURCE_FILES})

target_link_libraries("${PROJECT_NAME}" utils)
target_include_directories("${PROJECT_NAME}" PUBLIC ../utils)

foreach (F ${RESOURCE_FILES})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${F}
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${F}
            ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach ()