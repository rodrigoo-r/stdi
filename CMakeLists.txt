cmake_minimum_required(VERSION 3.30)
project(stdi C)

set(CMAKE_C_STANDARD 11)

add_library(stdi STATIC stdi.c
        stdi.h)
