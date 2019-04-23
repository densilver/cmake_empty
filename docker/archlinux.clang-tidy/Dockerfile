FROM archlinux/base:latest

ARG SRC_DIR=/usr/src/pet_console

ENV \
	TERM=xterm-color

RUN \
	pacman-db-upgrade && \
	pacman -Syyu --noconfirm

RUN \
	pacman -Syu --noconfirm make cmake clang && \
	pacman -Syu --noconfirm python python-pip && \
	python3 -m pip install pyyaml

RUN mkdir $SRC_DIR
COPY build.sh $SRC_DIR/build.sh
COPY scripts $SRC_DIR/scripts
COPY CMakeLists.txt $SRC_DIR/CMakeLists.txt
COPY src $SRC_DIR/src
COPY cmake $SRC_DIR/cmake

WORKDIR $SRC_DIR
RUN \
	CC=clang CXX=clang++ \
	PET_CONSOLE_BUILD_TYPE=Release \
	./build.sh rebuild

CMD python /usr/share/clang/run-clang-tidy.py -p .build/unix/Release
