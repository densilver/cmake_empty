#!/usr/bin/env sh

CMAKE_BIN=cmake

BUILD_TYPE=Debug

PROJECT_DIR=`pwd`
BUILD_DIR=build/${BUILD_TYPE}

if [[ "xrebuild" == "x$1" ]]; then
	rm -rf ${BUILD_DIR}
fi
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

${CMAKE_BIN} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ${PROJECT_DIR}
${CMAKE_BIN} --build . -- -j4

mkdir -p bin
cp -v src/app/app bin

cd ${PROJECT_DIR}

echo
echo run:
echo ./${BUILD_DIR}/bin/app
