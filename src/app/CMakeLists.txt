cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

if (EMSCRIPTEN)
set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(pet_console
	src/main.cpp
)

target_compile_features(pet_console PRIVATE cxx_std_11)
target_compile_options(pet_console PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	-Werror
)
