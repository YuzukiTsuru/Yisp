cmake_minimum_required(VERSION 3.14)
project(Yisp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/ftxui)

include_directories(
        src/
        lib/ftxui/include/
)

if (MSVC)
    add_definitions(-DMSVC)
endif ()

aux_source_directory(src SRC)

# Main program
add_executable(Yisp ${SRC})
target_link_libraries(Yisp PRIVATE ftxui::screen ftxui::dom ftxui::component)
if (MSVC)
    target_compile_options(Yisp PUBLIC "/utf-8")
endif ()

add_executable(test tests/ftxui-test.cpp)
target_link_libraries(test PRIVATE ftxui::screen ftxui::dom ftxui::component)