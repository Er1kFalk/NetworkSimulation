set(ETHERNET_SIMULATOR_SOURCES
    EthernetEvent.cpp
    EthernetEventRule.cpp
)

add_library(ethernet_simulator_lib STATIC ${ETHERNET_SIMULATOR_SOURCES})