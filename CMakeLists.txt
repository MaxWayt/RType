# Project name
project(RType-server)

cmake_minimum_required(VERSION 2.6)
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
SET(CMAKE_BUILD_TYPE Release)

add_subdirectory(dep/damncute)
add_subdirectory(src)
