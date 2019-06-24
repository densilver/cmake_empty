FROM ubuntu:19.04

ENV \
	TERM=xterm-color \
	SRC_DIR=/usr/src/pet_console

RUN \
	apt-get -y update && \
	apt-get install -y

RUN apt-get -y install cmake
RUN apt-get -y install g++

RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY scripts $SRC_DIR/scripts
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src

WORKDIR $SRC_DIR
RUN \
	PET_CONSOLE_BUILD_TYPE=Release \
	./build.sh rebuild

CMD ["./.build/unix/Release/bin/pet_console"]
