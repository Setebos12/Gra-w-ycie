# src/CMakeLists.txt

# Add the logic subdirectory
add_subdirectory(logic)
# add_subdirectory(input)
add_subdirectory(core)
# add_subdirectory(ui)
add_subdirectory(render)
# Add the main executable
add_subdirectory(input)

add_subdirectory(ui)


add_executable(${PROJECT_NAME} main.cpp)
# src/CMakeLists.txt

# Link the logic library to the main executable
target_link_libraries(${PROJECT_NAME} PRIVATE LogicModel)
#target_link_libraries(CMakeTarget PRIVATE InputTarget)
target_link_libraries(${PROJECT_NAME} PRIVATE CoreTarget)
#target_link_libraries(CMakeTarget PRIVATE UITarget)
target_link_libraries(${PROJECT_NAME} PRIVATE Renderer)

target_link_libraries(${PROJECT_NAME} PRIVATE InputTarget)

target_link_libraries(${PROJECT_NAME} PRIVATE  ui)

# sfml
target_link_libraries (${PROJECT_NAME} PRIVATE SFML::Graphics)
