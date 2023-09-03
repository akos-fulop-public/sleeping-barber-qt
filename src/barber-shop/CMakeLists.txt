add_library(barber-shop STATIC barberShop.cpp)

target_link_libraries(barber-shop PUBLIC Qt6::Core)

target_include_directories(barber-shop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
