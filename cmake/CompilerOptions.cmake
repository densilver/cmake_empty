function(set_default_target_compile_options target)
	target_compile_options(${target}
		PRIVATE
			-Wall
			-Wextra
			-Wpedantic
			-Werror

			-fno-rtti

			-fno-exceptions
			-fno-unwind-tables

			#-fchar8_t
	)
endfunction()

