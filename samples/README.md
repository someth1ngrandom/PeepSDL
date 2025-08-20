# Samples
These are example programs you can take a look at to learn how the API works.

## Building the samples
You will need:
- CMake (version 3.16 or higher)
- A C++ compiler (clang recommended)
- SDL3, SDL3_ttf, SDL3_mixer, SDL3_image along with their CMake toolchains
- The PeepSDL library and its headers (the examples link it statically)
- Being a human
- Having consciousness and intelligence
*The samples were made for Linux, if you don't use Linux modify them for whichever operating system you use*

<br>


1. Clone the repo
```bash
$ git clone https://github.com/someth1ngrandom/PeepSDL.git
```
2. Enter the samples folder
```bash
$ cd PeepSDL/samples
```
3. Pick any sample that you would like to build
4. Edit the CMakeLists.txt to point to where your library and headers are
5. Generate CMake files
```bash
$ cmake ..
```
6. Build
```bash
$ cmake --build . --parallel
```
7. ???
8. Profit!