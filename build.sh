#!/usr/bin/env sh

CMAKE_BIN=cmake

TARGET_PLATFORM=unix

BUILD_TYPE=Debug
SANETIZE=none

test "x${PET_CONSOLE_TARGET_PLATFORM}" = 'xemscripten' && TARGET_PLATFORM=${PET_CONSOLE_TARGET_PLATFORM}
test "x${PET_CONSOLE_BUILD_TYPE}" != 'x' && BUILD_TYPE=${PET_CONSOLE_BUILD_TYPE}
test "x${PET_CONSOLE_SANETIZE}" != 'x' && SANETIZE=${PET_CONSOLE_SANETIZE}

echo "target platform [${TARGET_PLATFORM}]"
echo "build type [${BUILD_TYPE}]"
echo "sanetize [${SANETIZE}]"

APP_NAME=pet_console

PROJECT_DIR=$PWD
BUILD_DIR=${PROJECT_DIR}/.build/${TARGET_PLATFORM}/${BUILD_TYPE}
BIN_DIR=${BUILD_DIR}/bin

test "x${1}" = 'xrebuild' && rm -rf ${BUILD_DIR}
${CMAKE_BIN} -E make_directory ${BUILD_DIR}

CMAKE_FLAGS="-DCMAKE_INSTALL_PREFIX=${BUILD_DIR}"
CMAKE_FLAGS="${CMAKE_FLAGS} -DCMAKE_BUILD_TYPE=${BUILD_TYPE}"

. ./scripts/building/platform/${TARGET_PLATFORM}.sh

cd ${BUILD_DIR}
build_platform_create_project
cd ${PROJECT_DIR}

${CMAKE_BIN} --build ${BUILD_DIR} --target install -- -j 8
build_platform_create_bin
