cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(NetworkSimTesting VERSION 0.0.1 LANGUAGES CXX)

set(SRCDIR_TEST src)
set(SRCDIR_NETWORKSIM ../NetworkSimulation/src)
file(GLOB SOURCES_TEST ${SRCDIR_TEST}/*.cpp ${SRCDIR_TEST}/*.h ${SRCDIR_TEST}/*/*.cpp ${SRCDIR_TEST}/*/*.h)
file(GLOB SOURCES_NETWORKSIM ${SRCDIR_NETWORKSIM}/*.cpp ${SRCDIR_NETWORKSIM}/*.h ${SRCDIR_NETWORKSIM}/*/*.cpp ${SRCDIR_NETWORKSIM}/*/*.h)
list(FILTER SOURCES_NETWORKSIM EXCLUDE REGEX ".*NetworkSimulator\\.cpp$") # exclude main file in networksimulation application

add_compile_options(-fPIC -fprofile-arcs -ftest-coverage)

add_executable(NetworkSimTesting
    ${SOURCES_TEST}
    ${SOURCES_NETWORKSIM}
)
target_include_directories(NetworkSimTesting PRIVATE ${SRCDIR_TEST} ${SRCDIR_NETWORKSIM})
target_link_libraries(NetworkSimTesting -lgtest -lgcov)
