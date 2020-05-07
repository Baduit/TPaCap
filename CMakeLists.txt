cmake_minimum_required(VERSION 3.12)

project(TPaCapProject VERSION 0.1 DESCRIPTION "Pcapng library")

add_subdirectory(lib)

add_executable(example ./src/main.cpp)
target_compile_features(example PRIVATE cxx_std_20)
target_compile_options(example
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
                       $<$<CXX_COMPILER_ID:GNU>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -g>)

target_include_directories(example PRIVATE ./lib)

include(CTest)
enable_testing(MAKE_DIRECTORY test)
add_subdirectory(test)