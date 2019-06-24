FROM archlinux/base:latest

ENV \
	TERM=xterm-color \
	SRC_DIR=/usr/src/pet_console

RUN \
	pacman-db-upgrade && \
	pacman -Syyu --noconfirm

RUN \
	pacman -Syu --noconfirm \
		clang emscripten make cmake

WORKDIR /root
RUN \
	echo "import os" > .emscripten && \
	echo "EMSCRIPTEN_ROOT = '/usr/lib/emscripten'" >> .emscripten && \
	echo "LLVM_ROOT = '/usr/lib/emscripten-llvm'" >> .emscripten && \
	echo "NODE_JS = '/usr/bin/node'" >> .emscripten && \
	echo "COMPILER_ENGINE = NODE_JS" >> .emscripten && \
	echo "JS_ENGINES = [NODE_JS]" >> .emscripten
RUN \
	source /etc/profile.d/emscripten.sh && \
	echo "int main() {}" > binaryen.cpp && \
	CC=clang CXX=clang++ em++ binaryen.cpp && \
	rm -v binaryen.*


RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY scripts $SRC_DIR/scripts
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src

WORKDIR $SRC_DIR
RUN \
	source /etc/profile.d/emscripten.sh && \
	PET_CONSOLE_TARGET_PLATFORM=emscripten \
	PET_CONSOLE_BUILD_TYPE=Release \
	./build.sh rebuild


WORKDIR $SRC_DIR/.build/emscripten/Release/bin
CMD python -m http.server 8000
