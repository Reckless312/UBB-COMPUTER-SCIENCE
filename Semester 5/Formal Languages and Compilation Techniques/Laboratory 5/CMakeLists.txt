cmake_minimum_required(VERSION 4.0)
project(Laboratory_5 C)

set(CMAKE_C_STANDARD 11)

add_executable(Laboratory_5 main.c
        automata.c
        automata.h
        grammar.c
        grammar.h)
