add_subdirectory(barber-shop)
add_subdirectory(customer-spawner)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE Qt6::Core)
