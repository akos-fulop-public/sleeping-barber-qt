add_executable(barberTest barberTest.cpp)
target_link_libraries(barberTest
    PRIVATE GTest::GTest
    PRIVATE barber
    PRIVATE Qt6::Core
    PRIVATE Qt6::Test)
gtest_discover_tests(barberTest)
