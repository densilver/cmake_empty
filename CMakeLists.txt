cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(pet_console VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(CompilerOptions)

add_subdirectory(src/app)
