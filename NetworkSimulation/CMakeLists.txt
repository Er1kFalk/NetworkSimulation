
# cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
# project(NetworkSimulation VERSION 0.0.1 LANGUAGES CXX)

# set(SRCDIR src)
# #file(GLOB LIBRARIES ${SRCDIR}/*.cpp ${SRCDIR}/*/*.cpp ${SRCDIR}/*/*/*.cpp ${SRCDIR}/*/*/*/*.cpp)

# add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

# add_subdirectory(${SRCDIR})


# # ADD_LIBRARY(SIMLIBS
# #     ${LIBRARIES} 
# # )

# add_executable(NetworkSimulation
#     ${SRCDIR}/NetworkSimulator.cpp
# )
# set_target_properties(
#     NetworkSimulation 
#     PROPERTIES 
#         OUTPUT_NAME "NetworkSimulation"
#         SUFFIX ".out"
# )

# #target_link_libraries(NetworkSimulation -lpcap)

# # config reader link
# target_link_libraries(NetworkSimulation config_reader_lib)

# # header generators link
# target_link_libraries(NetworkSimulation communication_protocol_lib)
# target_link_libraries(NetworkSimulation data_lib)
# target_link_libraries(NetworkSimulation ethernet_frame_lib)
# target_link_libraries(NetworkSimulation ipv4_packet_lib)
# target_link_libraries(NetworkSimulation tcp_segment_lib)

# # pcap writer link
# target_link_libraries(NetworkSimulation pcap_writer_lib)

# # simulator link
# target_link_libraries(NetworkSimulation base_scheduler_lib)
# target_link_libraries(NetworkSimulation ethernet_simulator_lib)
# target_link_libraries(NetworkSimulation ipv4_simulator_lib)
# target_link_libraries(NetworkSimulation network_node_simulator_lib)
# target_link_libraries(NetworkSimulation tcp_simulator_lib)

# # utility lib link
# target_link_libraries(NetworkSimulation array_utils_lib)
# target_link_libraries(NetworkSimulation bit_operations_lib)
# target_link_libraries(NetworkSimulation protocol_utils_lib)
# target_link_libraries(NetworkSimulation random_utils_lib)
# target_link_libraries(NetworkSimulation string_utils_lib)
# target_link_libraries(NetworkSimulation wayne_utils_lib)

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(NetworkSimulation VERSION 0.0.1 LANGUAGES CXX)

set(SRCDIR src)
set(PCAPDIR ${CMAKE_CURRENT_SOURCE_DIR}/src/CppToolkit-PCAP)
file(GLOB LIBRARIES ${SRCDIR}/*.cpp ${SRCDIR}/*/*.cpp ${SRCDIR}/*/*/*.cpp ${SRCDIR}/*/*/*/*.cpp ${SRCDIR}/*/*/*/*/*.cpp)

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