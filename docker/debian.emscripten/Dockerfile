FROM trzeci/emscripten-slim:latest

ARG SRC_DIR=/usr/src/pet_console

ENV \
	TERM=xterm-color

RUN \
	apt-get -y update && \
	apt-get install -y

RUN apt-get -y install make cmake

RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY scripts $SRC_DIR/scripts
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src
COPY cmake $SRC_DIR/cmake

WORKDIR $SRC_DIR
RUN \
	PET_CONSOLE_TARGET_PLATFORM=emscripten \
	PET_CONSOLE_BUILD_TYPE=Release \
	./build.sh rebuild

WORKDIR $SRC_DIR/.build/emscripten/Release/bin
#CMD python -m http.server 8000
