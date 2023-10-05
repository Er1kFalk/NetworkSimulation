//============================================================================
// Name        : EthernetHeader.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pcap.h>
#include <zlib.h>
#include <array>
#include <vector>
#include "EthernetHeader.h"
#include <stdexcept>
#include <algorithm>

class IPv4Frame {

};

//	std::vector<unsigned char> calculate_fcs(std::vector<unsigned char> ethernet_frame) {
//		uint32_t crc = crc32(0L, Z_NULL, 0);
//		for (unsigned char elem : ethernet_frame) {
//			crc = crc32(crc, &elem, 1);
//		}
//		std::vector<unsigned char> crc_vec = {
//				crc & 0xFF,
//				(crc >> 8) & 0xFF,
//				(crc >> 16) & 0xFF,
//				(crc >> 24) & 0xFF
//		};
//		return crc_vec;
//	}

//	void add_octets_to_frame(std::vector<unsigned char> octets) {
//		for (unsigned char o : octets) {
//			ethernet_frame.push_back(o);
//		}
//	}

void EthernetFrame::set_destination_address(std::vector<unsigned char> destination_address) {
	if (destination_address.size() == DESTINATION_ADDRESS_SIZE) {
		LLC_PDU::set_destination_address(destination_address);
	} else {
		// throw exception
	}
}

void EthernetFrame::set_source_address(std::vector<unsigned char> source_address) {
	if (source_address.size() == SOURCE_ADDRESS_SIZE) {
		LLC_PDU::set_source_address(source_address);
	} else {
		// throw exception
	}
}

void EthernetFrame::set_ethertype(std::string ethertype) {
	// make string lowercase
	std::transform(ethertype.begin(), ethertype.end(), ethertype.begin(),
			[](unsigned char c){return std::tolower(c);});
	// check if an ethertype conversion exists, otherwise throw exception
	auto i = this->ethertype_common_values.find(ethertype);
	if (i != this->ethertype_common_values.end()) {
		this->ethertype = i->second;
	} else {
		throw std::invalid_argument("Ethertype not in the ethertype_common_values table.");
	}
}

std::vector<unsigned char> EthernetFrame::get_header() {
	std::vector<std::vector<unsigned char>> header_values = {get_destination_address(), get_source_address(), ethertype};
	std::vector<unsigned char> header;
	for (auto i : header_values) {
		header.insert(header.end(), i.begin(), i.end());
	}

	return header;
}

std::vector<unsigned char> EthernetFrame::get_header_payload() {
	std::vector<unsigned char> header_payload = get_header();
	header_payload.insert(header_payload.end(), get_payload().begin(), get_payload().end());
	return header_payload;
}

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

//int main(int argc, char *argv[]) {
//////  EthernetFrame f{payload, {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x23}, {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x24}, {0x08, 0x00}};
//////  std::vector<unsigned char> pkt = f.get_ethernet_frame();
//////
//////  pcap_t *handle = pcap_open_dead(DLT_EN10MB, 1 << 16);
//////  pcap_dumper_t *dumper = pcap_dump_open(handle, "./test.pcap");
//////
//////  struct pcap_pkthdr pcap_hdr;
//////  pcap_hdr.caplen = f.get_ethernet_frame_size();
//////  pcap_hdr.len = pcap_hdr.caplen;
//////
//////  pcap_dump((u_char *)dumper, &pcap_hdr, pkt.data());
//////  pcap_dump_close(dumper);
//
//	return 0;
//}
