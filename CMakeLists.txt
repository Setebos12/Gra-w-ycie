# CMakeLists.txt

cmake_minimum_required (VERSION 3.29)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project ("gra-w-zycie")
 
# Include sub-projects.
add_subdirectory ("src")

# sfml
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# assets - make it so it updates after changes
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
