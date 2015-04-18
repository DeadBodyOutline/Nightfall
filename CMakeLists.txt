cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH})

ADD_DEFINITIONS(
    -Wall
    -std=c++11
)

project(ld32)

macro(thor_link_thor THOR_TARGET)
    target_link_libraries(${THOR_TARGET} thor)
endmacro()

add_subdirectory(src)
