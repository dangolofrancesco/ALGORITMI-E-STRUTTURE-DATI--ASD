cmake_minimum_required(VERSION 3.21)
project(E03 C)

set(CMAKE_C_STANDARD 99)

add_executable(E03 main.c personaggi.c personaggi.h inventario.c inventario.h)
