cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(nand-flash-emulator)
enable_language(C)

# location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    )

# location of header files
include_directories(
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/src
    )

add_library(nfe src/nfe.c)


# target to update git submodules
add_custom_target(
    update_submodules
    COMMAND git submodule init
    COMMAND git submodule update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )


set(UNITY_ROOT external/Unity CACHE STRING "Unity source root")

message(STATUS "UNITY_ROOT set to ${UNITY_ROOT}")

# unity includes
include_directories(
    ${PROJECT_SOURCE_DIR}/${UNITY_ROOT}
    ${PROJECT_SOURCE_DIR}/${UNITY_ROOT}/src
    )

# unity sources
set(UNITY_SOURCES
    ${PROJECT_SOURCE_DIR}/${UNITY_ROOT}/src/unity.c
    )

# mark these files as generated (they may not be present at configure time)
foreach(_source ${UNITY_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(unity ${UNITY_SOURCES})

# update git submodules before building google test
add_dependencies(unity update_submodules)

# unit test executable
add_executable(
    unit_tests
    test/main.c
    )

# unit test executable depends on unity
add_dependencies(unit_tests unity)

# link unit test executable against unity
target_link_libraries(
    unit_tests
    unity
    nfe
    )


# activate ctest
include(CTest)
enable_testing()

# define a test
add_test(unit ${PROJECT_BINARY_DIR}/unit_tests)

# make install and cpack
include(install_target)
