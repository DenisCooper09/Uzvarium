cmake_minimum_required(VERSION 3.20)

project(
        Uzvarium
        VERSION 1.0.0.0
        DESCRIPTION "The element of uzvar."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src bin)
