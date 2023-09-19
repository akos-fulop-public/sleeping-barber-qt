cmake_minimum_required(VERSION 3.22.1)

project("sleeping-barber" VERSION 1.0.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_COMPILE_WARNINGS_AS_ERRORS ON)
set(CMAKE_CXX_CPPLINT cpplint --repository=${CMAKE_SOURCE_DIR} --exclude=*/mocs_* --recursive --linelength=160 --filter=-legal/copyright,-whitespace/tab,-whitespace/braces)

add_compile_definitions(QT_NO_DEBUG_OUTPUT)

find_package(Qt6 COMPONENTS Core Test REQUIRED)
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
