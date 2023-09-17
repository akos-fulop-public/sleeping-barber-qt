add_subdirectory(barber)

add_executable(barber-shop-test barberShopTest.cpp)

target_link_libraries(barber-shop-test
    PRIVATE GTest::GTest
    PRIVATE barber-shop
    PRIVATE Qt6::Core
    PRIVATE Qt6::Test)

gtest_discover_tests(barber-shop-test)
