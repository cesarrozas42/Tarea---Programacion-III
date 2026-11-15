cmake_minimum_required(VERSION 3.20)
project(Tarea6Arboles CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

add_executable(tarea6 src/main.cpp)
