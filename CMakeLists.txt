cmake_minimum_required(VERSION 3.22.1)

project("sleeping-barber" VERSION 0.1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

message("${CMAKE_GENERATOR}")

find_package(Qt6 REQUIRED COMPONENTS Core)

add_subdirectory(src)
add_subdirectory(test)
