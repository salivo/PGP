cmake_minimum_required(VERSION 3.10)

project(PGP)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} raylib) 