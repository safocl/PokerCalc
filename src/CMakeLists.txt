cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(poker LANGUAGES CXX)

include_directories(../include)


#add_definitions(-O2)
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Werror)
#add_definitions(-Wno-parentheses)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CPPS *.cpp)
#set(CPPS MainWindow.cpp main.cpp)

add_library(${PROJECT_NAME} SHARED ${CPPS})

#target_link_libraries(${PROJECT_NAME} 
#                        poker)
