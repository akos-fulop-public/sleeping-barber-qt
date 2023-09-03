add_executable(barberShopTest barberShopTest.cpp)
target_link_libraries(barberShopTest
    PRIVATE GTest::GTest
    PRIVATE barber-shop
    PRIVATE Qt6::Core)
gtest_discover_tests(barberShopTest)
