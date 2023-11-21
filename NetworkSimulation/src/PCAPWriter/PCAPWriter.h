#ifndef PCAPWRITER_H_
#define PCAPWRITER_H_

#include <pcap/pcap.h>
#include <string>
#include <memory>
#include <vector>
#include "../WayneUtils/wayneEnums.hpp"


class PCAPWriter {
    pcap_t *packet_header;
    pcap_dumper_t *out_writer;
public:
    PCAPWriter(std::string filepath, wayne::PCAP::linkTypes ltype);

    ~PCAPWriter();

    void write_packet(std::vector<unsigned char> data, uint32_t seconds, uint32_t microseconds);
};

#endif