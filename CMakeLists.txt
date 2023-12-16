cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(LIBRARY_NAME aoc)

project(${LIBRARY_NAME} VERSION 1.0.0 LANGUAGES C CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

set(AOC_SOLUTIONS_DIR src/solutions)

add_library(${LIBRARY_NAME}
    STATIC
    src/utils/parse.cpp
    src/utils/Range.cpp
    ${AOC_SOLUTIONS_DIR}/day01.cpp
    ${AOC_SOLUTIONS_DIR}/day02.cpp
    ${AOC_SOLUTIONS_DIR}/day03.cpp
    ${AOC_SOLUTIONS_DIR}/day04.cpp
    ${AOC_SOLUTIONS_DIR}/day05.cpp
    ${AOC_SOLUTIONS_DIR}/day06.cpp
    ${AOC_SOLUTIONS_DIR}/day07.cpp
    ${AOC_SOLUTIONS_DIR}/day08.cpp
    ${AOC_SOLUTIONS_DIR}/day09.cpp
    ${AOC_SOLUTIONS_DIR}/day10.cpp
    ${AOC_SOLUTIONS_DIR}/day11.cpp
    ${AOC_SOLUTIONS_DIR}/day12.cpp
    ${AOC_SOLUTIONS_DIR}/day13.cpp
    ${AOC_SOLUTIONS_DIR}/day14.cpp
    ${AOC_SOLUTIONS_DIR}/day15.cpp
)

add_library(${LIBRARY_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(
    ${LIBRARY_NAME}
    PUBLIC
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic -O2>
)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME})

install(
    TARGETS ${LIBRARY_NAME}
    EXPORT ${LIBRARY_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(${LIBRARY_NAME} PROPERTIES EXPORT_NAME ${LIBRARY_NAME})

install(
    EXPORT ${LIBRARY_NAME}-targets
    FILE ${LIBRARY_NAME}Targets.cmake
    NAMESPACE ${LIBRARY_NAME}::
    DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${LIBRARY_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}ConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(
    EXPORT ${LIBRARY_NAME}-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Targets.cmake
    NAMESPACE ${LIBRARY_NAME}::
)

export(PACKAGE ${LIBRARY_NAME})

enable_testing()
add_subdirectory(test)