# src/CMakeLists.txt

# Add the logic subdirectory
add_subdirectory(logic)
# add_subdirectory(input)
add_subdirectory(core)
# add_subdirectory(ui)
add_subdirectory(render)
# Add the main executable
add_subdirectory(input)


add_executable(${PROJECT_NAME} main.cpp)
# src/CMakeLists.txt

# Link the logic library to the main executable
target_link_libraries(${PROJECT_NAME} PRIVATE LogicModel)
#target_link_libraries(CMakeTarget PRIVATE InputTarget)
target_link_libraries(${PROJECT_NAME} PRIVATE CoreTarget)
#target_link_libraries(CMakeTarget PRIVATE UITarget)
target_link_libraries(${PROJECT_NAME} PRIVATE Renderer)

target_link_libraries(${PROJECT_NAME} PRIVATE InputTarget)


# sfml
target_link_libraries (${PROJECT_NAME} PRIVATE SFML::Graphics)
