# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

project(main)

file(GLOB SOURCES include /*.hpp *.cpp)

file(
    GLOB_RECURSE
    SOURCES
    main.cpp
    src/*
)

add_executable(main ${SOURCES})

target_include_directories(main PUBLIC 
    "C:/Program Files (x86)/SFML/include"
    "C:/Users/thoma/perso-workspace/segment_d1/include"
)

target_link_directories(main PUBLIC "C:/Program Files (x86)/SFML/lib")
add_compile_definitions(SFML_STATIC)

target_link_libraries(main sfml-network-s)
target_link_libraries(main sfml-audio-s)
target_link_libraries(main sfml-graphics-s)
target_link_libraries(main sfml-window-s)
target_link_libraries(main sfml-system-s)
target_link_libraries(main ws2_32)
target_link_libraries(main openal32)
target_link_libraries(main flac)
target_link_libraries(main vorbisenc)
target_link_libraries(main vorbisfile)
target_link_libraries(main vorbis)
target_link_libraries(main ogg)
target_link_libraries(main freetype)
target_link_libraries(main opengl32)
target_link_libraries(main gdi32)
target_link_libraries(main winmm)
target_link_libraries(main psapi)
target_link_libraries(main pthread)

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
# target_compile_features(main PUBLIC cxx_std_20)
