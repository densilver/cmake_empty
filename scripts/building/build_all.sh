#!/usr/bin/env sh

DOCKER_BIN=docker
APP_NAME=pet_console

PET_CONSOLE_BUILD_TYPE=Release ./build.sh rebuild
.build/unix/Release/bin/pet_console

docker pull archlinux/base:latest

docker build -f docker/ubuntu.gcc/Dockerfile -t pet_console:gcc .
docker run --rm -it pet_console:gcc

docker build -f docker/archlinux.clang-ubsan/Dockerfile -t pet_console:ubsan .
docker run --rm -it pet_console:ubsan

docker build -f docker/archlinux.clang-valgrind/Dockerfile -t pet_console:valgrind .
docker run --rm -it pet_console:valgrind

docker build -f docker/archlinux.clang-tidy/Dockerfile -t pet_console:tidy .
docker build -f docker/archlinux.emscripten/Dockerfile -t pet_console:emscripten .
