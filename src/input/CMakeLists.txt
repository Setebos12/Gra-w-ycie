# src/input/CMakeLists.txt

project("Input")

set(SOURCE
    input.cpp
    inputpoller.cpp
)

add_library(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    Core
)
