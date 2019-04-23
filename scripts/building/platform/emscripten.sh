build_platform_create_project() {
	flags=${CMAKE_FLAGS}

	test "${SANETIZE}" != 'none' && flags="${flags} -DPET_CONSOLE_SANETIZE=1"
	echo ${flags}

	emcmake ${CMAKE_BIN} \
		${flags} \
		${PROJECT_DIR} || exit 1
}

build_platform_create_bin() {
	${CMAKE_BIN} -E copy \
		${BUILD_DIR}/src/app/${APP_NAME}.js \
		${BUILD_DIR}/src/app/${APP_NAME}.wasm \
		${BIN_DIR}

	echo
	echo "run:"
	echo "pushd ${BIN_DIR}; python -m SimpleHTTPServer 8000; popd"
	echo
	echo "open:"
	echo "http://localhost:8000/${APP_NAME}.html"
}
