# src/input/CMakeLists.txt

# Add a library for the input module
add_library(InputTarget
    Input.cpp
    Input.h
    ParserKeyboard.h
    ParserKeyboard.cpp
    InputToken.h "InputButton.h")

# Include the current directory for header files
target_link_libraries(InputTarget PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(InputTarget PRIVATE ${SFML_INCLUDE_DIRS})
target_include_directories(InputTarget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})