cmake_minimum_required(VERSION 3.27)
project(TypingTest C)

set(CMAKE_C_STANDARD 11)

add_executable(TypingTest main.c
        textreading.c
        textreading.h)
