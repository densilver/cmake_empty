FROM archlinux/base:latest

ENV \
	TERM=xterm-color \
	SRC_DIR=/usr/src/pet_empty

RUN \
	pacman-db-upgrade && \
	pacman -Syyu --noconfirm && \
	pacman -Syu --noconfirm make cmake
RUN pacman -Syu --noconfirm clang

RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src

WORKDIR $SRC_DIR
RUN sh ./build.sh rebuild
CMD ["./.build/Debug/bin/app"]