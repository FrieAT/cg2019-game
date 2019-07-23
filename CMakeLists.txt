cmake_minimum_required (VERSION 2.8)
project (2019_cg_physics) 

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-gdwarf-2 -g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Add local repository for FindXXX.cmake modules.
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

set(PACKAGE_STRING 2019_cg_physics)
set(PACKAGE_BUGREPORT held@cosy.sbg.ac.at)
set(PACKAGE_VERSION 1.0)

option(WITH_GLUT "Building with GLUT library" "ON")
option(WITH_GLFW "Building with GLFW library" "ON")
option(WITH_GLEW "Building with GLEW library" "ON")

# More verbose output by make
# set(CMAKE_VERBOSE_MAKEFILE "ON")

add_subdirectory(src)




