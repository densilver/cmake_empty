FROM ubuntu:19.04

ARG SRC_DIR=/usr/src/pet_console

ENV \
	TERM=xterm-color

RUN \
	apt-get -y update && \
	apt-get install -y

RUN apt-get -y install make cmake
RUN apt-get -y install g++-9

RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY scripts $SRC_DIR/scripts
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src
COPY cmake $SRC_DIR/cmake

WORKDIR $SRC_DIR
RUN \
	CC=gcc-9 CXX=g++-9 \
	PET_CONSOLE_BUILD_TYPE=Release \
	./build.sh rebuild

CMD ["./.build/unix/Release/bin/pet_console"]
