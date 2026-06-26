cmake_minimum_required(VERSION 4.1)
project(COP3530_Project2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(COP3530_Project2
        src/main.cpp
        src/dataset.cpp
        src/dataset.h
        src/recipe_graph.cpp
        src/recipe_graph.h
        src/recipe_BFS.cpp
        src/recipe_BFS.h
        src/recipe_DFS.cpp
        src/recipe_DFS.h)
