cmake_minimum_required(VERSION 3.22.1)

project("sleeping-barber" VERSION 1.0.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

add_compile_definitions(QT_NO_DEBUG_OUTPUT)

find_package(Qt6 COMPONENTS Core Test REQUIRED)
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
