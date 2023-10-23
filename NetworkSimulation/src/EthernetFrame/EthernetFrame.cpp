//============================================================================
// Name        : EthernetFrame.cpp
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
#include "EthernetFrame.h"
#include <stdexcept>
#include <algorithm>
#include <list>
#include "ArrayUtils/ArrayUtils.h"
#include "MACAddress/MACAddress.h"
#include "IPv4Packet/IPv4PacketInterface.h"
#include "IPv4Packet/IPv4Packet.h"
#include "TrafficClass/TrafficClass.h"
#include "ProtocolType/ProtocolType.h"
#include "IPv4Address/IPv4Address.h"

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



void EthernetFrame::set_destination_address(MACAddressInterface *destination_address) {
	this->destination_address = destination_address;
}


void EthernetFrame::set_source_address(MACAddressInterface *source_address) {
	this->source_address = source_address;
}

std::vector<unsigned char> EthernetFrame::to_array() {
	std::vector<unsigned char> header_payload_array;
	for (unsigned char c : get_destination_address()->get_address()) {
		header_payload_array.push_back(c);
	}

	for (unsigned char c : get_source_address()->get_address()) {
		header_payload_array.push_back(c);
	}
	
	for (unsigned char c : ethertype->get_ethertype()) {
		header_payload_array.push_back(c);
	}
	return header_payload_array;
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

// int main(int argc, char *argv[]) {
// ////  EthernetFrame f{payload, {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x23}, {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x24}, {0x08, 0x00}};
// ////  std::vector<unsigned char> pkt = f.get_ethernet_frame();
// ////
// ////  pcap_t *handle = pcap_open_dead(DLT_EN10MB, 1 << 16);
// ////  pcap_dumper_t *dumper = pcap_dump_open(handle, "./test.pcap");
// ////
// ////  struct pcap_pkthdr pcap_hdr;
// ////  pcap_hdr.caplen = f.get_ethernet_frame_size();
// ////  pcap_hdr.len = pcap_hdr.caplen;
// ////
// ////  pcap_dump((u_char *)dumper, &pcap_hdr, pkt.data());
// ////  pcap_dump_close(dumper);
// 	EthernetFrame etherframe;
// 	EthertypeInterface *protocol = new Ethertype;
// 	protocol->set_ethertype((std::array<unsigned char, 2>) {0x08, 0x00});

// 	MACAddressInterface *destination = new MACAddress;
// 	destination->set_address((std::array<unsigned char, 6>){0x01, 0x02, 0x03, 0x04, 0x05, 0x06});

// 	MACAddressInterface *source = new MACAddress;
// 	source->set_address((std::array<unsigned char, 6>){0x01, 0x02, 0x03, 0x04, 0x05, 0x06});

// 	etherframe.set_ethertype(protocol);
// 	etherframe.set_destination_address(destination);
// 	etherframe.set_source_address(source);
	
// 	IPv4PacketInterface *packet = new IPv4Packet;
// 	TrafficClassInterface *tclass = new TrafficClass;
// 	tclass->set_ds(0);
// 	tclass->set_ecn(0);

// 	ProtocolTypeInterface *network_protocol = new ProtocolType;
// 	network_protocol->set_protocol(0x01);

// 	IPv4AddressInterface *source_ip = new IPv4Address;
// 	IPv4AddressInterface *destination_ip = new IPv4Address;

// 	source_ip->set_address({0x01, 0x02, 0x03, 0x04});
// 	destination_ip->set_address({0xAB, 0xFF, 0xDD, 0x22});

// 	Data data;
// 	data.set_data({0x01, 0x02, 0x04});
// 	data.set_payload(nullptr);

// 	packet->set_payload(&data);
// 	packet->set_version();
// 	packet->set_ihl();
// 	packet->set_type_of_service(tclass);
// 	packet->set_total_length();
// 	packet->set_identification(0);
// 	packet->set_df_flag(true);
// 	packet->set_mf_flag(false);
// 	packet->set_fragment_offset(0);
// 	packet->set_time_to_live(64);
// 	packet->set_protocol(network_protocol);
// 	packet->set_header_checksum();
// 	packet->set_source(source_ip);
// 	packet->set_destination(destination_ip);

// 	etherframe.set_payload(packet);

	
// 	//std::vector<unsigned char> print = packet->to_array();
// 	CommunicationProtocol *print = &etherframe;
// 	while(print != nullptr) {
// 		std::vector<unsigned char> printarr = print->to_array();
// 		for (unsigned char c : printarr) {
// 			std::cout << std::hex << (int) c << " ";
// 		}
// 		std::cout << std::endl;

// 		print = print->get_payload();
// 	}

// 	return 0;
// }
