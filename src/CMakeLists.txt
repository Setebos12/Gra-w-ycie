# src/CMakeLists.txt

# Add the input subdirectory
add_subdirectory(input)

# Add the main executable
add_executable(CMakeTarget "main.cpp")

# Link the input library to the main executable
target_link_libraries(CMakeTarget PRIVATE InputTarget)

# Set the C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()