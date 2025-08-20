cmake_minimum_required(VERSION 3.16)
project(BasicWindowSample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PEEPSDL_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../../include") # point to your includes
set(PEEPSDL_LIBRARY_PATH "/usr/local/lib/libPeepSDL.a") # point to where the library is

add_executable(BasicWindowSample
    main.cpp
)

# so we dont die
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_image REQUIRED)

target_link_libraries(BasicWindowSample PRIVATE "${PEEPSDL_LIBRARY_PATH}" SDL3::SDL3-shared SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer SDL3_image::SDL3_image)

target_include_directories(BasicWindowSample PUBLIC "${PEEPSDL_INCLUDE_PATH}") # point to your includes