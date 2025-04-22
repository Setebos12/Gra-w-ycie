# src/logic/CMakeLists.txt

# Add a library for the input module
add_library(LogicTarget
    board.cpp
    board.h
    Container.h
    PointHandle.h)

# Include the current directory for header files
target_include_directories(LogicTarget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
