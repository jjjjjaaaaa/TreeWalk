cmake_minimum_required(VERSION 3.10)

project(TreeWalk)

add_library(TreeWalkLib
    src/TreeWalk.cpp
)
target_include_directories(TreeWalkLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(TreeWalkTest main.cpp test/test.cpp)
target_include_directories(TreeWalkTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TreeWalkTest TreeWalkLib)
