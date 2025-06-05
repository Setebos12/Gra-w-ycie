# src/ui/CMakeLists.txt
project("Ui")

set(SOURCE
	hud.cpp
	uipanel.cpp
	inputbutton.cpp
)

add_library(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC SFML::Graphics Core PRIVATE LogicModel)
