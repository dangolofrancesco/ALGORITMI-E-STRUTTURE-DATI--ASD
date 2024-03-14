cmake_minimum_required(VERSION 3.21)
project(ADT C)

set(CMAKE_C_STANDARD 99)

add_executable(ADT main.c complex.c complex.h Item.c Item.h list.c list.h Set.c Set.h Stack.c Stack.h queue.c queue.h PQ.c PQ.h ST.c ST.h)
