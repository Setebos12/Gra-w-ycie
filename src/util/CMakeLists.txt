# src/util/CMakeLists.txt

project("Util")

set (SOURCE
	logger.cpp
	fileIO.cpp
)

add_library(${PROJECT_NAME} ${SOURCE})

# Include the current directory for header files
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
