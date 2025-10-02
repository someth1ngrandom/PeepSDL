cmake_minimum_required(VERSION 3.16)
project(PeepSDLTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PEEPSDL_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../include")
set(PEEPSDL_LIBRARY_PATH "/usr/local/lib/libPeepSDL.a")

add_executable(PeepSDLTest
    main.cpp
)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_image REQUIRED)

target_link_libraries(PeepSDLTest PRIVATE "${PEEPSDL_LIBRARY_PATH}" SDL3::SDL3-shared SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer SDL3_image::SDL3_image)

target_include_directories(PeepSDLTest PUBLIC "${PEEPSDL_INCLUDE_PATH}")