cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(NetworkSimulation VERSION 0.0.1 LANGUAGES CXX)

set(SRCDIR src)
file(GLOB SOURCES ${SRCDIR}/*.cpp ${SRCDIR}/*.h ${SRCDIR}/*/*.cpp ${SRCDIR}/*/*.h)

add_executable(NetworkSimulation
    ${SOURCES}
)
target_include_directories(NetworkSimulation PRIVATE ${SRCDIR})
