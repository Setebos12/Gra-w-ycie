# src/core/CMakeLists.txt

project(Sim)

set(SOURCE
	simulation.cpp
)

# Add a library for the logic module
add_library(${PROJECT_NAME} ${SOURCE})

# Include the current directory for header files
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
PRIVATE
	Util
	Renderer
	Input
	SFML::Graphics
	LogicModel
	Ui
)
