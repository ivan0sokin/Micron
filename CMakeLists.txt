cmake_minimum_required(VERSION 3.0)
project(Micron)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/core/Timer.cpp
                 src/core/Logger.cpp
                )

set(CMAKE_BUILD_TYPE Release)
add_library(micron STATIC ${SOURCE_FILES})