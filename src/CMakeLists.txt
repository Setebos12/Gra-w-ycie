# src/CMakeLists.txt

# Add the logic subdirectory
add_subdirectory(util)
add_subdirectory(logic)
add_subdirectory(input)
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(render)
add_subdirectory(simulation)

# Add the main executable
add_executable(${PROJECT_NAME} main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
	LogicModel
	Input
	Core
	Ui
	Renderer
	Util
	Sim
)

# sfml
target_link_libraries (${PROJECT_NAME} PRIVATE SFML::Graphics)
