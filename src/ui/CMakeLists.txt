# src/ui/CMakeLists.txt
project("ui")

# Add a library for the input module
set(SOURCE
	hud.cpp
)

# Include the current directory for header files
add_library(${PROJECT_NAME} ${SOURCE})

# Include the current directory for header files
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC SFML::Graphics)
