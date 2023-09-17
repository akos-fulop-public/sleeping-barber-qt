add_library(customer-spawner STATIC customerSpawner.cpp)

target_link_libraries(customer-spawner PUBLIC Qt6::Core)

target_include_directories(customer-spawner INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
