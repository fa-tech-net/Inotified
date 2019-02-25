cmake_minimum_required(VERSION 2.6)
project(Inotified)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(Inotified COMMAND make -C ${Inotified_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})
