cmake_minimum_required(VERSION 3.29)

set(This GOLTests)

set(Sources
	BoardTest.cpp
	ContainerTest.cpp
	PointHandleTest.cpp
)

add_executable(${This} ${Sources})

include(CTest)

target_link_libraries(${This} PUBLIC
	gtest_main
	LogicModel
	Renderer
	ui
)

add_test(
	NAME ${This}
	COMMAND ${This}
)

include(GoogleTest)
gtest_discover_tests(${This})