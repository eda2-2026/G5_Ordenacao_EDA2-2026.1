cmake_minimum_required(VERSION 3.26)
project(G5_Ordenacao_EDA2_2026_1 CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(src)

add_executable(G5_Ordenacao_EDA2_2026_1
        src/main.cpp
        src/RadixSort.h
        src/MergeSort.h
        src/DataManager.h
        src/PerformerTimer.h)
 
find_package(Threads REQUIRED)
target_link_libraries(G5_Ordenacao_EDA2_2026_1 Threads::Threads)
 