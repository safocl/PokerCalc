cmake_minimum_required(VERSION 3.5)

project(poker LANGUAGES CXX)

include_directories(../include)


#add_definitions(-O2)
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Werror)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CPPS *.cpp)
#set(CPPS MainWindow.cpp main.cpp)

add_library(${PROJECT_NAME} SHARED ${CPPS})

#target_link_libraries(${PROJECT_NAME} 
#                        poker)
