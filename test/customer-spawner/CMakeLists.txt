add_executable(customer-spawner-test customerSpawnerTest.cpp)

target_link_libraries(customer-spawner-test
    PRIVATE GTest::GTest
    PRIVATE Qt6::Core
    PRIVATE Qt6::Test
    PRIVATE customer-spawner)

gtest_discover_tests(customer-spawner-test)
