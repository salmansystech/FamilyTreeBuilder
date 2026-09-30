cmake_minimum_required(VERSION 3.10)
project(FamilyTreeBuilder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(family
    family/main.cpp
    family/familytree.cpp
    family/cli.cpp
    family/utils.cpp
)

target_include_directories(family PRIVATE family/)
