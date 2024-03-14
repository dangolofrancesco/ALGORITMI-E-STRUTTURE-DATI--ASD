cmake_minimum_required(VERSION 3.24)
project(E03 C)

set(CMAKE_C_STANDARD 99)

add_executable(E03 main.c data.h data.c titolo.h quotazione.h quotazione.c quotazioni.h quotazioni.c titolo.c titoli.h titoli.c)
