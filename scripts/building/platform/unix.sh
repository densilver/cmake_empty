build_platform_create_project() {
	${CMAKE_BIN} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
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
