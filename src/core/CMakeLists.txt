# src/core/CMakeLists.txt

# Add a library for the logic module
add_library(CoreTarget
    gameobject.h
)

# Include the current directory for header files
target_include_directories(CoreTarget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
