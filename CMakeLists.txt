cmake_minimum_required(VERSION 3.29)
project(CanteenSystem C)

set(CMAKE_C_STANDARD 11)

add_executable(main
        print_table.c)
file(GLOB sources CONFIGURE_DEPENDS *.c *.h)
target_sources(main PUBLIC ${sources})