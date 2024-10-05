add_executable(PGP_tests
    main_tests.cpp
    test_body.cpp
    test_space.cpp
    test_thread.cpp
    test_space_tasker.cpp
    ${SRC_FILES})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/tests/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(PGP_tests raylib)

add_test(body PGP_tests "1")
add_test(space PGP_tests "2")
add_test(thread PGP_tests "3")
add_test(tasker PGP_tests "4")
add_test(modular PGP_tests "5")
