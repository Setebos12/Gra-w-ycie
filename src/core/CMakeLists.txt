# src/core/CMakeLists.txt

# Add a library for the logic module
add_library(CoreTarget
    Simulation.cpp
	gameobject.cpp
)

# Include the current directory for header files
target_include_directories(CoreTarget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CoreTarget PRIVATE SFML::Graphics)
target_link_libraries(CoreTarget PRIVATE Renderer)
target_link_libraries(CoreTarget PRIVATE LogicModel)
target_link_libraries(CoreTarget PRIVATE InputTarget)
