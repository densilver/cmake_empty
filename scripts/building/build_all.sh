#!/usr/bin/env sh

PET_CONSOLE_BUILD_TYPE=Release ./build.sh rebuild
.build/unix/Release/bin/pet_console

docker pull ubuntu:19.10
docker build -f docker/ubuntu.gcc/Dockerfile -t pet_console:gcc .
docker run --rm -it pet_console:gcc

docker pull archlinux/base:latest
docker build -f docker/archlinux.clang-valgrind/Dockerfile -t pet_console:valgrind .
docker run --rm -it pet_console:valgrind

docker build -f docker/archlinux.clang-tidy/Dockerfile -t pet_console:tidy .
docker run --rm -it pet_console:tidy

docker build -f docker/archlinux.emscripten/Dockerfile -t pet_console:emscripten_arch .

docker pull debian:buster-slim
docker build -f docker/debian.emscripten/Dockerfile -t pet_console:emscripten_debian .
