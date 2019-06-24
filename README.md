###### Debug Build
````bash
./build.sh
````

###### Release Build
````bash
PET_CONSOLE_BUILD_TYPE=Release ./build.sh rebuild
````

###### Emscripten Debug Build
````bash
PET_CONSOLE_TARGET_PLATFORM=emscripten ./build.sh
````

###### Local Undefined Behavior Sanitizer
````bash
PET_CONSOLE_SANETIZE=UBSan ./build.sh
./.build/unix/Debug/bin/pet_console
````

###### Dockerized Undefined Behavior Sanitizer
````bash
docker build -f docker/archlinux.clang-ubsan/Dockerfile -t pet_console:ubsan .
docker run --rm -it pet_console:ubsan
````

###### Dockerized CLang-Tidy
````bash
docker build -f docker/archlinux.clang-tidy/Dockerfile -t pet_console:tidy .
````

###### Dockerized valgrind
````bash
docker build -f docker/archlinux.clang-valgrind/Dockerfile -t pet_console:valgrind .
docker run --rm -it pet_console:valgrind
````

###### Dockerized emscripten
````bash
docker build -f docker/archlinux.emscripten/Dockerfile -t pet_console:emscripten .
docker run --rm -it pet_console:emscripten
````
