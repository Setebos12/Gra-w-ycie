# src/core/CMakeLists.txt

# Add a library for the logic module
add_library(CoreTarget
    Simulation.h
    Simulation.cpp
    Logger.h
    gameobject.h
	gameobject.cpp
)

# Include the current directory for header files
target_include_directories(CoreTarget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CoreTarget PRIVATE SFML::Graphics)
