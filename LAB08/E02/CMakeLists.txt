cmake_minimum_required(VERSION 3.24)
project(E02 C)

set(CMAKE_C_STANDARD 99)

add_executable(E02 main.c Graph.h Graph.c Item.h Item.c ST.h ST.c)
