add_executable(customerSpawnerTest customerSpawnerTest.cpp)
target_link_libraries(customerSpawnerTest
    PRIVATE GTest::GTest
    PRIVATE GTest::Main
    PRIVATE customerSpawner)
gtest_discover_tests(customerSpawnerTest)
