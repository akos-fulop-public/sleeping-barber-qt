add_executable(customerSpawnerTest customerSpawnerTest.cpp)
target_link_libraries(customerSpawnerTest
    PRIVATE GTest::GTest
    PRIVATE customerSpawner
    PRIVATE Qt6::Core
    PRIVATE Qt6::Test)
gtest_discover_tests(customerSpawnerTest)
