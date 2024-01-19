set(TCP_SIMULATOR_SOURCES
    TCPEvent.cpp
    TCPEventRules.cpp
)

add_library(tcp_simulator_lib STATIC ${TCP_SIMULATOR_SOURCES})