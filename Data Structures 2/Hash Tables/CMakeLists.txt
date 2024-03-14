cmake_minimum_required(VERSION 3.24)
project(Tabelle_di_Hash C)

set(CMAKE_C_STANDARD 99)

add_executable(Tabelle_di_Hash main.c ST.h ST.c OpenAddressing.h OpenAddressing.c)
