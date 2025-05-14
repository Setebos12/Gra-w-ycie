# src/render/CMakeLists.txt

project("Renderer")

set (SOURCE
	drawer.cpp
)

add_library(${PROJECT_NAME} ${SOURCE})

# Include the current directory for header files
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC SFML::Graphics)
