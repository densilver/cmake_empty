cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(app
	src/main.cpp
)

target_compile_features(app PRIVATE cxx_std_11)
target_compile_options(app PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	-Werror
)
