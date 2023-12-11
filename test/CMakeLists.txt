find_package(GTest QUIET)

if(NOT GTEST_FOUND)
    configure_file(
        ${CMAKE_SOURCE_DIR}/cmake/GoogleTest-CMakeLists.txt.in
        ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
    )

    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
    )

    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    add_subdirectory(
        ${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL
    )
endif()

add_executable(aoc_test
    src/day01-test.cpp
    src/day02-test.cpp
    src/day03-test.cpp
    src/day04-test.cpp
    src/day05-test.cpp
    src/day06-test.cpp
    src/day07-test.cpp
    src/day08-test.cpp
    src/day09-test.cpp
    src/day10-test.cpp
    src/main.cpp)

target_link_libraries(aoc_test gtest aoc::aoc)
target_compile_definitions(aoc_test PUBLIC TXT_FILE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/files/")
add_test(
    NAME aoc_test
    COMMAND aoc_test
)