cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(NetworkSimTesting VERSION 0.0.1 LANGUAGES CXX)
SET(CMAKE_BUILD_TYPE Debug)

set(SRCDIR_TEST src)
set(SRCDIR_NETWORKSIM ../NetworkSimulation/src)

file(GLOB SOURCES_TEST ${SRCDIR_TEST}/*.cpp ${SRCDIR_TEST}/*/*.cpp)

file(GLOB SOURCES_NETWORKSIM ${SRCDIR_NETWORKSIM}/*.cpp ${SRCDIR_NETWORKSIM}/*/*.cpp ${SRCDIR_NETWORKSIM}/*/*/*.cpp)
list(FILTER SOURCES_NETWORKSIM EXCLUDE REGEX ".*NetworkSimulator\\.cpp$") # exclude main file in networksimulation application
list(FILTER SOURCES_NETWORKSIM EXCLUDE REGEX ".*Archived/.*")

include(CMakePrintHelpers)
cmake_print_variables(SOURCES_NETWORKSIM)


add_compile_options(-fPIC -fprofile-arcs -ftest-coverage)

add_library(NetworkSimulationLibrary
    ${SOURCES_NETWORKSIM}
)

add_executable(NetworkSimTesting
    ${SOURCES_TEST}
    src/tests/Helpers/TCPSegmentHelper.h
)
target_include_directories(NetworkSimTesting PRIVATE ${SRCDIR_TEST} ${SRCDIR_NETWORKSIM})
target_link_libraries(NetworkSimTesting NetworkSimulationLibrary -lgtest -lgcov -lpcap)
