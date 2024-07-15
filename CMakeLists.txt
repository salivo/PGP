cmake_minimum_required(VERSION 3.10)

project(PGP)

add_executable(${PROJECT_NAME} src/main.cpp src/process_bodies.cpp src/gui_elements.cpp src/calc_helper.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external)

target_link_libraries(${PROJECT_NAME} raylib)
