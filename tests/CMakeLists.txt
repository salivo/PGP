add_executable(cpp_test main.cpp ${SRC_FILES})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(cpp_test raylib)

add_test(ok_test cpp_test "1")
add_test(procces_thread cpp_test "2")
# add_test(cpp_test cpp_test "3")
