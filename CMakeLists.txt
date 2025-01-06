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

target_compile_options(main PRIVATE
    -isystem "C:/Users/thoma/perso-workspace/segment_d1/include"
)

target_link_directories(main PUBLIC "C:/Program Files (x86)/SFML/lib")

add_compile_definitions(SFML_STATIC)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wzero-as-null-pointer-constant -Wswitch-default -Wswitch-enum -Wmissing-include-dirs -Wunreachable-code -Winline -Winit-self -Wnon-virtual-dtor -pedantic -ansi -Wcast-qual -Wdisabled-optimization -Wdiv-by-zero -Wendif-labels -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winvalid-pch -Wmissing-braces -Wmultichar -Wpacked -Wpointer-arith -Wreturn-type -Wsequence-point -Wvariadic-macros -Wfloat-equal -Wstrict-aliasing=1 -Wstrict-overflow=5 -Wunsafe-loop-optimizations -Wnull-dereference -Wuninitialized -Wstringop-overflow=4 -Wstringop-truncation -Walloc-zero -Walloca -Wduplicated-branches -Wduplicated-cond -Wtrampolines -Wunused-macros -Wconditionally-supported -Wdate-time -Wvarargs -Wvector-operation-performance -Wopenmp-simd -Whsa -Wextra-semi -Warray-bounds=2 -Wformat-truncation=2 -Wunused-const-variable=1 -Wuseless-cast -Wold-style-cast -Wsign-promo -Wvirtual-inheritance -Wstrict-null-sentinel -Wsync-nand -Wunused-parameter -Wunused -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=malloc -Wmissing-noreturn -Wmissing-format-attribute -Wimplicit-fallthrough=5 -Wif-not-aligned -Wformat-signedness -Wsuggest-override -Wsuggest-final-methods -Wsuggest-final-types -Wstack-protector -Wenum-compare -Wlong-long -Wmultiple-inheritance -Wdouble-promotion -Wsign-conversion -Wfloat-conversion -Wconversion -Wnoexcept -Wnoexcept-type -Wclass-memaccess -Wregister -Wctor-dtor-privacy -Wsynth -Wlto-type-mismatch -Wliteral-suffix -Wdelete-non-virtual-dtor")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wzero-as-null-pointer-constant -Wswitch-default -Wswitch-enum -Wmissing-include-dirs -Wunreachable-code -Winline -Winit-self -Wnon-virtual-dtor -pedantic -Wcast-qual -Wdisabled-optimization -Wdiv-by-zero -Wendif-labels -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winvalid-pch -Wmissing-braces -Wmultichar -Wpacked -Wpointer-arith -Wreturn-type -Wsequence-point -Wvariadic-macros -Wfloat-equal -Wstrict-aliasing=1 -Wstrict-overflow=5 -Wunsafe-loop-optimizations -Wnull-dereference -Wuninitialized -Wstringop-overflow=4 -Wstringop-truncation -Walloc-zero -Walloca -Wduplicated-branches -Wduplicated-cond -Wtrampolines -Wunused-macros -Wconditionally-supported -Wdate-time -Wvarargs -Wvector-operation-performance -Wopenmp-simd -Whsa -Wextra-semi -Warray-bounds=2 -Wformat-truncation=2 -Wunused-const-variable=1 -Wuseless-cast -Wold-style-cast -Wsign-promo -Wvirtual-inheritance -Wstrict-null-sentinel -Wsync-nand -Wunused-parameter -Wunused -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=malloc -Wmissing-noreturn -Wmissing-format-attribute -Wimplicit-fallthrough=5 -Wif-not-aligned -Wformat-signedness -Wsuggest-override -Wsuggest-final-methods -Wsuggest-final-types -Wstack-protector -Wenum-compare -Wlong-long -Wmultiple-inheritance -Wdouble-promotion -Wsign-conversion -Wfloat-conversion -Wconversion -Wnoexcept -Wnoexcept-type -Wclass-memaccess -Wregister -Wctor-dtor-privacy -Wsynth -Wlto-type-mismatch -Wliteral-suffix -Wdelete-non-virtual-dtor -Wno-unused -Wno-missing-format-attribute -Wc++17-compat -Wpadded")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-function-type")
# -ansi
# -Wnamespaces
# -Wtemplates
# -Wabi-tag -Wsystem-headers -Wpadded -Waggregate-return

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

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/assets")
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
