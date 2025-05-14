# src/CMakeLists.txt

# Add the logic subdirectory
#add_subdirectory(logic)
# add_subdirectory(input)
add_subdirectory(core)
# add_subdirectory(ui)
add_subdirectory(render)
# Add the main executable
add_executable(CMakeTarget "main.cpp" "logic/Container.cpp" "logic/PointHandle.cpp")
# src/CMakeLists.txt

# Link the logic library to the main executable
#target_link_libraries(CMakeTarget PRIVATE LogicTarget)
#target_link_libraries(CMakeTarget PRIVATE InputTarget)
target_link_libraries(CMakeTarget PRIVATE CoreTarget)

#target_link_libraries(CMakeTarget PRIVATE UITarget)
target_link_libraries(CMakeTarget PRIVATE Renderer)

# sfml
target_link_libraries (CMakeTarget PRIVATE SFML::Graphics)

# Set the C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()
