cmake_minimum_required(VERSION 3.21)
project(ADT_Heap C)

set(CMAKE_C_STANDARD 99)

add_executable(ADT_Heap main.c Heap.c Heap.h PQ.c PQ.h PQindex.c PQindex.h)
