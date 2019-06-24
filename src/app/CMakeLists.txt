cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

add_executable(pet_console
	src/main.cpp
)

target_compile_features(pet_console
	PRIVATE
		cxx_std_11
)
target_compile_options(pet_console
	PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Werror
)

install(TARGETS pet_console
	RUNTIME DESTINATION bin
)

if (PET_CONSOLE_SANETIZE)
	target_compile_options(pet_console
		PRIVATE
			-fsanitize=undefined
	)
	target_link_options(pet_console
		PRIVATE
			-fsanitize=undefined
	)
endif()
