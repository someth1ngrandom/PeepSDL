cmake_minimum_required(VERSION 3.16)
project(PeepSDL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_library(PeepSDL STATIC
    # src/main.cpp

    src/class/Window.cpp
    src/class/Rect.cpp
    src/class/Color.cpp
    src/class/Transform.cpp
    src/class/Texture.cpp
    src/class/Random.cpp
    src/class/Text.cpp
    src/class/Audio.cpp
)

# when using this lib link these or you die

# find_package(SDL3 REQUIRED)
# find_package(SDL3_ttf REQUIRED)
# find_package(SDL3_mixer REQUIRED)
# find_package(SDL3_image REQUIRED)

# target_link_libraries(YOURTARGET PRIVATE SDL3::SDL3-shared SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer SDL3_image::SDL3_image)

target_include_directories(PeepSDL PUBLIC "${CMAKE_SOURCE_DIR}/include")

include(GNUInstallDirs)
install(TARGETS PeepSDL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
