cmake_minimum_required(VERSION 3.15)
project("AoC-2020")

# Set all binaries compiled with C++20 flags by default.
set(CMAKE_CXX_STANDARD "20")
# Export compile_commands.json file.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("day01")
add_subdirectory("day02")
