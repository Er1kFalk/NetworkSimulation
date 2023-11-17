cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(NetworkSimulation VERSION 0.0.1 LANGUAGES CXX)

set(SRCDIR src)
file(GLOB LIBRARIES ${SRCDIR}/*.cpp ${SRCDIR}/*/*.cpp ${SRCDIR}/*/*/*.cpp)
#file(GLOB SOURCES ${SRCDIR}/*.h ${SRCDIR}/*/*.h ${SRCDIR}/*/*/*.h ${SRCDIR}/NetworkSimulator.cpp)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)
#list(FILTER SOURCES EXCLUDE REGEX ".*Archived/.*")
list(FILTER LIBRARIES EXCLUDE REGEX ".*Archived/.*")

ADD_LIBRARY(LibsModule 
    ${LIBRARIES}
)


add_executable(NetworkSimulation
    ${SRCDIR}/NetworkSimulator.cpp
)
set_target_properties(
    NetworkSimulation 
    PROPERTIES 
        OUTPUT_NAME "NetworkSimulation"
        SUFFIX ".out"
)

target_include_directories(NetworkSimulation PRIVATE ${SRCDIR})
target_link_libraries(LibsModule -lpcap)
target_link_libraries(NetworkSimulation LibsModule)
