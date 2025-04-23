# src/logic/CMakeLists.txt

# Add a library for the logic module
add_library(LogicTarget
    logic.h)

# Include the current directory for header files
target_include_directories(LogicTarget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
