cmake_minimum_required(VERSION 3.10)

project(TreeWalk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(TreeWalkTest test/test.cpp)
target_include_directories(TreeWalkTest PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include /usr/local/include/)
target_link_directories(TreeWalkTest PRIVATE /usr/local/lib)

add_executable(TreeWalkPerformanceTest main.cpp)
target_include_directories(TreeWalkPerformanceTest PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include /usr/local/include/)
target_link_libraries(TreeWalkPerformanceTest -flto)
target_link_directories(TreeWalkPerformanceTest PRIVATE /usr/local/lib)
