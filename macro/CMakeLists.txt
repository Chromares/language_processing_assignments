cmake_minimum_required(VERSION 3.6)
project(macro_pro)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c mdt.h mnt.h para_tables.h mdt.c mnt.c para_tables.c)
add_executable(macro_pro ${SOURCE_FILES})