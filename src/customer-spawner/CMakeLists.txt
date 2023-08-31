add_library(customerSpawner STATIC customerSpawner.cpp)
target_include_directories(customerSpawner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(customerSpawner PUBLIC Qt6::Core)
