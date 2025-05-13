# src/render/CMakeLists.txt

project(Renderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SOURCE
	drawer.cpp
	renderer.cpp
)

# Add a library for the input module
add_library(${PROJECT_NAME} ${SOURCE})

# Include the current directory for header files
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Renderer PRIVATE SFML::Graphics)
