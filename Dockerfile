FROM archlinux/base:latest

ENV \
	TERM=xterm-color \
	SRC_DIR=/usr/src/pet_console

RUN \
	pacman-db-upgrade && \
	pacman -Syyu --noconfirm

RUN pacman -Syu --noconfirm make cmake gcc emscripten

WORKDIR /root
RUN \
	echo "import os" > .emscripten && \
	echo "EMSCRIPTEN_ROOT = '/usr/lib/emscripten'" >> .emscripten && \
	echo "LLVM_ROOT = '/usr/lib/emscripten-fastcomp'" >> .emscripten && \
	echo "NODE_JS = '/usr/bin/node'" >> .emscripten && \
	echo "COMPILER_ENGINE = NODE_JS" >> .emscripten && \
	echo "JS_ENGINES = [NODE_JS]" >> .emscripten
RUN \
	echo "int main() {}" > binaryen.cpp && \
	/usr/lib/emscripten/emcc binaryen.cpp && \
	rm -f binaryen.cpp

RUN \
	pacman -Syu --noconfirm npm && \
	npm install -g static-server

RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY scripts $SRC_DIR/scripts
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src

WORKDIR $SRC_DIR
RUN \
	PATH=/usr/lib/emscripten:$PATH \
	PET_CONSOLE_TARGET_PLATFORM=emscripten \
	./build.sh rebuild


WORKDIR $SRC_DIR/.build/emscripten/Debug/bin
CMD static-server -p 8000 -i pet_console.html
