cmake_minimum_required(VERSION 3.5)
project(Assembler_2pass)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(SOURCE_FILES main.c location_counter.c location_counter.h sym_table.c sym_table.h op_table.c op_table.h)
add_executable(Assembler_2pass ${SOURCE_FILES})