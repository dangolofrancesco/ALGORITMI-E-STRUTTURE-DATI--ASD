cmake_minimum_required(VERSION 3.24)
project(E01 C)

set(CMAKE_C_STANDARD 99)

add_executable(E01 main.c Graph.h Graph.c ST.h ST.c Item.h Item.c)
