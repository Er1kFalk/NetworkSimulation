set(PCAP_WRITER_SOURCES
    PCAPWriter.cpp
)

add_library(pcap_writer_lib STATIC ${PCAP_WRITER_SOURCES})
target_link_libraries(pcap_writer_lib -lpcap)