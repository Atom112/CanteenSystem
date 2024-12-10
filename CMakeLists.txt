cmake_minimum_required(VERSION 3.29)
project(CanteenSystem CXX)

set(CMAKE_C_STANDARD 11)
add_executable(main

)
file(GLOB sources CONFIGURE_DEPENDS *.cpp *.h)
target_sources(main PUBLIC ${sources})