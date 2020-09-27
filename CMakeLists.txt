cmake_minimum_required(VERSION 3.0)
project(Micron)

set(CMAKE_CXX_STANDARD 20 REQUIRED)

set(SOURCE_FILES src/core/Exceptions.cpp
                 src/core/Timer.cpp
                 src/core/Logger.cpp
                )

set(CMAKE_BUILD_TYPE Release)
add_library(micron STATIC ${SOURCE_FILES})