cmake_minimum_required(VERSION 3.10)

project(PGP)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/process_thread.cpp
    src/bodies.cpp
    src/calc_helper.cpp
    src/gui_elements/gui_main.cpp
    src/gui_elements/control_panel.cpp
    src/gui_elements/body_finder.cpp
    src/gui_elements/body_params.cpp
    src/gui_elements/params_changer.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external)

target_link_libraries(${PROJECT_NAME} raylib)

#  __  Tests  __

add_executable(cpp_test tests/main.cpp)

# enable testing functionality
enable_testing()

# define tests
add_test(
  NAME cpp_test
  COMMAND $<TARGET_FILE:cpp_test>
  )
