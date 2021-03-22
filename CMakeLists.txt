cmake_minimum_required(VERSION 3.14)
project(Yisp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
        src/
)

if (MSVC)
    add_definitions(-DMSVC)
endif ()

aux_source_directory(src SRC)

# Main program
add_executable(Yisp ${SRC})