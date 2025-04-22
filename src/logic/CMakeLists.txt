# CMakeList.txt : CMake project for Gra w życie, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakeTarget "board.cpp" "board.h" "Container.h" "PointHandle.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
