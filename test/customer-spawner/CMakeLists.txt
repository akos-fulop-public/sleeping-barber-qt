add_executable(customer-spawner-test customerSpawnerTest.cpp)

target_link_libraries(customer-spawner-test
    PRIVATE GTest::GTest
    PRIVATE customer-spawner
    PRIVATE Qt6::Core
    PRIVATE Qt6::Test)

gtest_discover_tests(customer-spawner-test)
