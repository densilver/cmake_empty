build_platform_create_project() {
	flags=${CMAKE_FLAGS}
	flags="${flags} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"

	test "${SANETIZE}" != 'none' && flags="${flags} -DPET_CONSOLE_SANETIZE=1"
	echo ${flags}

	${CMAKE_BIN} \
		${flags} \
		${PROJECT_DIR}
}

build_platform_create_bin() {
	echo "done"
}
