//============================================================================
// Name        : NetworkSim.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <pcap.h>
#include <stdint.h>
#include <array>
#include <vector>

template <std::size_t mac_octet_amount = 6, std::size_t ethertype_octet_amount = 2, std::size_t fcs_octet_amount = 4>
class EthernetFrame {

	std::vector<unsigned char> ethernet_frame;

	// sets the next octet_amount octets from first_octet
	// e.g. if first_octet = 6, octet_amount = 6, it will set octet 6-11
	void set_octets_ethernet_frame (int first_octet, int parameter, int octet_amount) {

	}

public:
	std::vector<unsigned char> get_ethernet_frame() {
		return ethernet_frame;
	}

	uint32_t get_ethernet_frame_size() {
		return ethernet_frame.size();
	}

	EthernetFrame (std::vector<unsigned char> payload, std::array<unsigned char, mac_octet_amount> destination_address, std::array<unsigned char, mac_octet_amount> source_address, std::array<unsigned char, ethertype_octet_amount> ethertype) {
			for (unsigned char elem : destination_address) {
				ethernet_frame.push_back(elem);
			}
			for (unsigned char elem : source_address) {
				ethernet_frame.push_back(elem);

			}
			for (unsigned char elem : ethertype) {
				ethernet_frame.push_back(elem);
			}
			for (unsigned char elem : payload) {
				ethernet_frame.push_back(elem);
			}
			// missing fcs
	}
};

static const unsigned char pkt1[86] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x45, 0x00, /* ......E. */
  0x00, 0x44, 0x55, 0xb1, 0x00, 0x00, 0x40, 0x84, /* .DU...@. */
  0x26, 0x83, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00, /* &....... */
  0x00, 0x01, 0x00, 0x01, 0x1f, 0x90, 0x00, 0x00, /* ........ */
  0x00, 0x00, 0x68, 0xe5, 0x88, 0x1b, 0x01, 0x00, /* ..h..... */
  0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, /* .$...... */
  0xa0, 0x00, 0x00, 0x04, 0xff, 0xff, 0x00, 0x00, /* ........ */
  0x16, 0x2e, 0x80, 0x00, 0x00, 0x04, 0xc0, 0x00, /* ........ */
  0x00, 0x04, 0x00, 0x0c, 0x00, 0x06, 0x00, 0x05, /* ........ */
  0x00, 0x00, 0x12, 0xAB, 0x11, 0x00                    /* .. */
};

std::vector<unsigned char> payload = {
		0x45, 0x00, /* ......E. */
		0x00, 0x44, 0x55, 0xb1, 0x00, 0x00, 0x40, 0x84, /* .DU...@. */
		0x26, 0x83, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00, /* &....... */
		0x00, 0x01, 0x00, 0x01, 0x1f, 0x90, 0x00, 0x00, /* ........ */
		0x00, 0x00, 0x68, 0xe5, 0x88, 0x1b, 0x01, 0x00, /* ..h..... */
		0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, /* .$...... */
		0xa0, 0x00, 0x00, 0x04, 0xff, 0xff, 0x00, 0x00, /* ........ */
		0x16, 0x2e, 0x80, 0x00, 0x00, 0x04, 0xc0, 0x00, /* ........ */
		0x00, 0x04, 0x00, 0x0c, 0x00, 0x06, 0x00, 0x05, /* ........ */
		0x00, 0x00
};

int main(int argc, char *argv[]) {
  EthernetFrame<> f{payload, {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x23}, {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x24}, {0x08, 0x00}};
  std::vector<unsigned char> pkt = f.get_ethernet_frame();

  pcap_t *handle = pcap_open_dead(DLT_EN10MB, 1 << 16);
  pcap_dumper_t *dumper = pcap_dump_open(handle, "./test.pcap");

  struct pcap_pkthdr pcap_hdr;
  pcap_hdr.caplen = f.get_ethernet_frame_size();
  pcap_hdr.len = pcap_hdr.caplen;

  pcap_dump((u_char *)dumper, &pcap_hdr, pkt.data());
  pcap_dump((u_char *)dumper, &pcap_hdr, pkt.data());
  pcap_dump_close(dumper);

  return 0;
}
