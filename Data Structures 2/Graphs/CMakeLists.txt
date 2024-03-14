cmake_minimum_required(VERSION 3.21)
project(GRAFO C)

set(CMAKE_C_STANDARD 99)

add_executable(GRAFO main.c Graph.c ST.c queue.h UF.h UF.c PQ.h)
