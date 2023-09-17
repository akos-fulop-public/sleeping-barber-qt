add_library(barber STATIC barber.cpp)

target_link_libraries(barber PUBLIC Qt6::Core)

target_include_directories(barber INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
