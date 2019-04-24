#!/usr/bin/env sh

CMAKE_BIN=cmake

BUILD_TYPE=Debug

PROJECT_DIR=$PWD
BUILD_DIR=.build/${BUILD_TYPE}
BIN_DIR=${BUILD_DIR}/bin

test "xrebuild" = "x${1}" && rm -rf ${BUILD_DIR}
${CMAKE_BIN} -E make_directory ${BUILD_DIR}

cd ${BUILD_DIR}
${CMAKE_BIN} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ${PROJECT_DIR}
cd ${PROJECT_DIR}

${CMAKE_BIN} --build ${BUILD_DIR} -- -j 8

${CMAKE_BIN} -E make_directory ${BIN_DIR}
${CMAKE_BIN} -E copy ${BUILD_DIR}/src/app/app ${BIN_DIR}

echo
echo run:
echo ./${BIN_DIR}/app
