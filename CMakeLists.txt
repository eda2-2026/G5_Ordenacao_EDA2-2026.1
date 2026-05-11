cmake_minimum_required(VERSION 3.26)
project(G5_Ordenacao_EDA2_2026_1 CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(src)

add_executable(G5_Ordenacao_EDA2_2026_1
        src/main.cpp)

add_executable(TestRadixSort
        tests/TestRadixSort.cpp)

add_executable(TestMergeSort
        tests/TestMergeSort.cpp)

find_package(Threads REQUIRED)
target_link_libraries(G5_Ordenacao_EDA2_2026_1 Threads::Threads)
target_link_libraries(TestMergeSort Threads::Threads)
 