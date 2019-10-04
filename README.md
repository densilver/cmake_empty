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
````

###### Dockerized CLang-Tidy
````bash
docker build -f docker/archlinux.clang-tidy/Dockerfile -t pet_console:tidy .
docker run --rm -it pet_console:tidy
````

###### Dockerized valgrind
````bash
docker build -f docker/archlinux.clang-valgrind/Dockerfile -t pet_console:valgrind .
docker run --rm -it pet_console:valgrind
````

###### Dockerized emscripten
````bash
docker build -f docker/archlinux.emscripten/Dockerfile -t pet_console:emscripten_arch .
docker run --rm -it pet_console:emscripten_arch
````

###### Dockerized emscripten
````bash
docker build -f docker/debian.emscripten/Dockerfile -t pet_console:emscripten_debian .
docker run --rm -it pet_console:emscripten_debian
````
