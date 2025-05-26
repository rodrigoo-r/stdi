cmake_minimum_required(VERSION 3.30)
project(stdi C)

set(CMAKE_C_STANDARD 11)

add_library(stdi STATIC include/fluent/stdi/library.c
        include/fluent/stdi/library.h)
