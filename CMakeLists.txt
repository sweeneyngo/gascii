# cmake version
cmake_minimum_required(VERSION 3.0.0)

# project name
project(gascii VERSION 0.1.0)

# flags

# files

# include

include_directories( 
    ./include
    ./src
    ./lib
    ./lib/gopt )


# target
add_executable( 
    gascii 
    ./src/main.cpp 
    ./src/ASCII.cpp
    ./lib/gopt/gopt-errors.cpp
    ./lib/gopt/gopt.cpp )

# opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(gascii ${OpenCV_LIBS})

# testing
include(CTest)
enable_testing()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(OpenCV_DIR=/usr/include/opencv4)
include(CPack)
