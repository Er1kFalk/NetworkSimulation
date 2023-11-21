
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(NetworkSimulation VERSION 0.0.1 LANGUAGES CXX)

set(SRCDIR src)
set(PCAPDIR ${CMAKE_CURRENT_SOURCE_DIR}/src/CppToolkit-PCAP)
file(GLOB LIBRARIES ${SRCDIR}/*.cpp ${SRCDIR}/*/*.cpp ${SRCDIR}/*/*/*.cpp)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)
list(FILTER LIBRARIES EXCLUDE REGEX ".*Archived/.*")
#list(FILTER LIBRARIES EXCLUDE REGEX ".*CppToolkit-PCAP/.*")



include(CMakePrintHelpers)
cmake_print_variables(LIBRARIES)

ADD_LIBRARY(SIMLIBS
    ${LIBRARIES} 
)

add_executable(NetworkSimulation
    ${LIBRARIES}
)
set_target_properties(
    NetworkSimulation 
    PROPERTIES 
        OUTPUT_NAME "NetworkSimulation"
        SUFFIX ".out"
)

target_include_directories(NetworkSimulation PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${PCAPDIR}
)

target_link_libraries(NetworkSimulation -lpcap)
#target_link_libraries(NetworkSimulation ${PCAPDIR}/)

#target_link_libraries(NetworkSimulation SIMLIBS)

#target_link_libraries(PCAPNG2 PRIVATE PCAPNG1)
#target_link_libraries(NetworkSimulation PCAPNGWRITERLIB)

