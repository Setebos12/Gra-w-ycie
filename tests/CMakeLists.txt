cmake_minimum_required(VERSION 3.29)

set(This GOLTests)

set(Sources
	BoardTest.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
	gtest_main
	LogicModel
)

add_test(
	NAME ${This}
	COMMAND ${This}
)
