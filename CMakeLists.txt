cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(testmem64 C CXX ASM)
add_executable(testmem64 testmem64.c )
