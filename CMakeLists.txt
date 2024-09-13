cmake_minimum_required(VERSION 3.10)

project(PGP)

enable_testing()

set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/process_thread.cpp
    ${PROJECT_SOURCE_DIR}/src/bodies.cpp
    ${PROJECT_SOURCE_DIR}/src/calc_helper.cpp
)
set(SRC_GUI_FILES
    ${PROJECT_SOURCE_DIR}/src/gui_elements/gui_main.cpp
    ${PROJECT_SOURCE_DIR}/src/gui_elements/control_panel.cpp
    ${PROJECT_SOURCE_DIR}/src/gui_elements/body_finder.cpp
    ${PROJECT_SOURCE_DIR}/src/gui_elements/body_params.cpp
    ${PROJECT_SOURCE_DIR}/src/gui_elements/params_changer.cpp
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SRC_FILES}
    ${SRC_GUI_FILES}
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME} raylib)

add_subdirectory(tests)
