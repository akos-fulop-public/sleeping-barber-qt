add_executable(barber-test barberTest.cpp)

target_link_libraries(barber-test
	PRIVATE GTest::GTest
	PRIVATE Qt6::Core
	PRIVATE Qt6::Test
	PRIVATE barber)

gtest_discover_tests(barber-test)
