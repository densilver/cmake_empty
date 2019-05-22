build_platform_create_project() {
	emconfigure ${CMAKE_BIN} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		${PROJECT_DIR}
}

build_platform_create_bin() {
	${CMAKE_BIN} -E copy \
		${BUILD_DIR}/src/app/${APP_NAME}.js \
		${BUILD_DIR}/src/app/${APP_NAME}.wasm \
		${BUILD_DIR}/src/app/${APP_NAME}.html \
		${BIN_DIR}

	echo
	echo "run:"
	echo "pushd ./${BIN_DIR}; python2 -m SimpleHTTPServer 8000; popd"
	echo
	echo "open:"
	echo "http://localhost:8000/${APP_NAME}.html"
}
