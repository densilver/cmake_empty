cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

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
set_default_target_compile_options(pet_console)

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
