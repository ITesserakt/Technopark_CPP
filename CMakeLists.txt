cmake_minimum_required(VERSION 3.20)
project(Technopark_CPP)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CURRENT_TASK 1)
include(InstallLibraries.cmake)

add_executable(main main.cpp)

add_subdirectory(individual-task-${CURRENT_TASK})

target_include_directories(main PRIVATE individual-task-${CURRENT_TASK}/include)
target_link_libraries(main PRIVATE it-${CURRENT_TASK})
