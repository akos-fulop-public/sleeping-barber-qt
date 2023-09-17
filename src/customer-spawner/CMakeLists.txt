add_library(customerSpawner STATIC customerSpawner.cpp)

target_link_libraries(customerSpawner PUBLIC Qt6::Core)

target_include_directories(customerSpawner INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
