enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests test.cpp test.cpp)
target_link_libraries(tests GTest::GTest GTest::Main)
gtest_discover_tests(tests)
