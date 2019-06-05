FROM archlinux/base:latest

ENV \
	TERM=xterm-color \
	SRC_DIR=/usr/src/pet_console

RUN \
	pacman-db-upgrade && \
	pacman -Syyu --noconfirm

RUN pacman -Syu --noconfirm make cmake clang

RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY scripts $SRC_DIR/scripts
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src

WORKDIR $SRC_DIR
RUN \
	CXX=clang++ \
	PET_CONSOLE_BUILD_TYPE=Release \
	PET_CONSOLE_SANETIZE=UBSan \
	./build.sh rebuild

CMD ["./.build/unix/Release/bin/pet_console"]
