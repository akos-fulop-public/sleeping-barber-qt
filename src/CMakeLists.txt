add_subdirectory(barber-shop)
add_subdirectory(customer-spawner)

add_executable(app main.cpp)

target_link_libraries(app
	PRIVATE Qt6::Core
	PRIVATE barber-shop
	PRIVATE customer-spawner
	PRIVATE barber)

install(TARGETS app DESTINATION ".")
