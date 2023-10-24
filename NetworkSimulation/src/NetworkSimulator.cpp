#include "EthernetFrame/EthernetFrameInterface.h"
#include "EthernetFrame/EthernetFrame.h"
#include "MACAddress/MACAddressInterface.h"
#include "MACAddress/MACAddress.h"
#include "IPv4Packet/IPv4PacketInterface.h"
#include "IPv4Packet/IPv4Packet.h"
#include "TrafficClass/TrafficClassInterface.h"
#include "TrafficClass/TrafficClass.h"
#include "ProtocolType/ProtocolTypeInterface.h"
#include "ProtocolType/ProtocolType.h"
#include "IPv4Address/IPv4AddressInterface.h"
#include "IPv4Address/IPv4Address.h"

#include <iostream>

int main(int argc, char *argv[]) {
////  EthernetFrame f{payload, {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x23}, {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x24}, {0x08, 0x00}};
////  std::vector<unsigned char> pkt = f.get_ethernet_frame();
////
////  pcap_t *handle = pcap_open_dead(DLT_EN10MB, 1 << 16);
////  pcap_dumper_t *dumper = pcap_dump_open(handle, "./test.pcap");
////
////  struct pcap_pkthdr pcap_hdr;
////  pcap_hdr.caplen = f.get_ethernet_frame_size();
////  pcap_hdr.len = pcap_hdr.caplen;
////
////  pcap_dump((u_char *)dumper, &pcap_hdr, pkt.data());
////  pcap_dump_close(dumper);
	std::shared_ptr<EthernetFrameInterface> etherframe(new EthernetFrame(
		std::shared_ptr<MACAddressInterface>(new MACAddress({0x01, 0x02, 0x03, 0x04, 0x05, 0x06})),
		std::shared_ptr<MACAddressInterface>(new MACAddress({0x01, 0x02, 0x03, 0x04, 0x05, 0x06})),
		std::shared_ptr<EthertypeInterface>(new Ethertype({0x08, 0x00})),
		std::shared_ptr<IPv4PacketInterface>(new IPv4Packet(
			std::shared_ptr<TrafficClassInterface>(new TrafficClass(0, 0)),
			0, // identification
			false,
			false,
			0, // offset
			64, // time_to_live
			std::shared_ptr<ProtocolTypeInterface>(new ProtocolType(0x01)),
			std::shared_ptr<IPv4AddressInterface>(new IPv4Address({0x01, 0x02, 0x03, 0x04})),
			std::shared_ptr<IPv4AddressInterface>(new IPv4Address({0xAB, 0xFF, 0xDD, 0x22})),
			std::shared_ptr<CommunicationProtocol>(new Data({0x01, 0x02, 0x04}))
		)
		)
	)
	);
	// EthertypeInterface *protocol = new Ethertype;
	// protocol->set_ethertype((std::array<unsigned char, 2>) {0x08, 0x00});

	// MACAddressInterface *destination = new MACAddress;
	// destination->set_address((std::array<unsigned char, 6>){0x01, 0x02, 0x03, 0x04, 0x05, 0x06});

	// MACAddressInterface *source = new MACAddress;
	// source->set_address((std::array<unsigned char, 6>){0x01, 0x02, 0x03, 0x04, 0x05, 0x06});

	// etherframe->set_ethertype(protocol);
	// etherframe->set_destination_address(destination);
	// etherframe->set_source_address(source);
	
	// IPv4PacketInterface *packet = new IPv4Packet(
	// 	new TrafficClass(0, 0),
	// 	0, // identification
	// 	false,
	// 	false,
	// 	0, // offset
	// 	64, // time_to_live
	// 	new ProtocolType(0x01),
	// 	new IPv4Address({0x01, 0x02, 0x03, 0x04}),
	// 	new IPv4Address({0xAB, 0xFF, 0xDD, 0x22}),
	// 	new Data({0x01, 0x02, 0x04}, nullptr)
	// );

	// etherframe->set_payload(packet);

	
	std::shared_ptr<CommunicationProtocol> print(etherframe);
	while(print != nullptr) {
		std::vector<unsigned char> printarr = print->to_array();
		for (unsigned char c : printarr) {
			std::cout << std::hex << (int) c << " ";
		}
		std::cout << std::endl;

		print = print->get_payload();
	}

	return 0;
}