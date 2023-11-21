#include "PCAPWriter.h"
#include <stdexcept>

PCAPWriter::PCAPWriter(std::string filepath, wayne::PCAP::linkTypes ltype) {
    this->packet_header = pcap_open_dead(ltype, 1 << 16);
    this->out_writer = pcap_dump_open(this->packet_header, filepath.c_str());

    if (this->out_writer == NULL) {
        char *errmsg = pcap_geterr(this->packet_header);
        throw std::invalid_argument(errmsg);
    }
}

PCAPWriter::~PCAPWriter() {
    pcap_dump_close(this->out_writer);
}

void PCAPWriter::write_packet(std::vector<unsigned char> data, uint32_t seconds, uint32_t microseconds) {
    struct pcap_pkthdr pcap_hdr;
    struct timeval timestamp;
    timestamp.tv_sec = seconds;
    timestamp.tv_usec = microseconds;
    
    pcap_hdr.caplen = data.size();
    pcap_hdr.len = pcap_hdr.caplen;
    pcap_hdr.ts = timestamp;

    pcap_dump((u_char *) this->out_writer, &pcap_hdr, data.data());
}
