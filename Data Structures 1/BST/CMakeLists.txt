cmake_minimum_required(VERSION 3.21)
project(BST C)

set(CMAKE_C_STANDARD 99)

add_executable(BST main.c BST_ext.h BST_ext.c ADT_BST.c)
