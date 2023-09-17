add_executable(barber-test barberTest.cpp)

target_link_libraries(barber-test
    PRIVATE GTest::GTest
    PRIVATE barber
    PRIVATE Qt6::Core
    PRIVATE Qt6::Test)

gtest_discover_tests(barber-test)
