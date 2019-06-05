build_platform_create_project() {
	local flags="-DCMAKE_BUILD_TYPE=${BUILD_TYPE}"
	flags="${flags} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"

	test "${SANETIZE}" != 'none' && flags="${flags} -DPET_CONSOLE_SANETIZE=1"

	${CMAKE_BIN} \
		${flags} \
		${PROJECT_DIR}
}

build_platform_create_bin() {
	${CMAKE_BIN} -E copy \
		${BUILD_DIR}/src/app/${APP_NAME} \
		${BIN_DIR}

	echo
	echo "run:"
	echo ./${BIN_DIR}/${APP_NAME}
}
