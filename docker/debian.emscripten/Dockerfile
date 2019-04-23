FROM debian:buster-slim

ARG SRC_DIR=/usr/src/pet_console

ENV \
	TERM=xterm-color

RUN \
	apt-get -y update
RUN \
	apt-get -y install git python make cmake

WORKDIR /root
RUN \
	mkdir emsdk

WORKDIR /root/emsdk
RUN \
	git init && \
	git remote add origin https://github.com/emscripten-core/emsdk.git && \
	git pull --rebase origin master
RUN \
	./emsdk install latest && \
	./emsdk activate latest

WORKDIR /root

RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY scripts $SRC_DIR/scripts
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src
COPY cmake $SRC_DIR/cmake

WORKDIR $SRC_DIR
RUN \
	PATH=$PATH:/root/emsdk:/root/emsdk/upstream/emscripten:/root/emsdk/node/12.9.1_64bit/bin \
	PET_CONSOLE_TARGET_PLATFORM=emscripten \
	PET_CONSOLE_BUILD_TYPE=Release \
	./build.sh rebuild

WORKDIR $SRC_DIR/.build/emscripten/Release/bin
CMD python -m CGIHTTPServer
