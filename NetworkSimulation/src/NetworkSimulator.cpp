#include "HeaderGenerators/EthernetFrame/EthernetFrame.h"
#include "HeaderGenerators/IPv4Packet/IPv4Packet.h"
#include "HeaderGenerators/ProtocolConstants/ProtocolConstants.h"
#include "HeaderGenerators/TCPSegment/TCPSegment.h"
#include "UtilityLibraries/ArrayUtils/ArrayUtils.h"
#include "UtilityLibraries/ProtocolUtils/ProtocolUtils.h"
#include "Simulator/NetworkNodeSimulator/NetworkNodeSimulator.h"
#include "Simulator/NetworkProperties.h"
#include "PCAPWriter/PCAPWriter.h"

#include <bits/stdc++.h>

#include <iostream>

#include <tuple>

#include <cstdlib>
#include <math.h>

#include <pcap/pcap.h>
#include "Simulator/TCPSimulator/TCPEvent.h"


int main(int argc, char *argv[]) {
	std::vector<std::string> args;
	std::string filename;
	int simulation_time;
	double rtt_mean;
	double rtt_stddev;

	for (int i = 0; i < argc; i++) {
		args.push_back(std::string(argv[i]));
	}

	std::cout << "Enter output filename (include .pcap extension) : ";
	std::cin >> filename;
	std::cout << std::endl << "Enter simulation time: ";
	std::cin >> simulation_time;
	std::cout << std::endl << "Enter round trip time mean (ms) for the network: ";
	std::cin >> rtt_mean;
	std::cout << std::endl << "Enter round trip time standard deviation (ms) for the network: ";
	std::cin >> rtt_stddev;


	auto n1configs = std::shared_ptr<ConfigReader>(new ConfigReader(args));

	auto writer = std::shared_ptr<PCAPWriter>(new PCAPWriter(filename, wayne::PCAP::linkTypes::LINKTYPE_ETHERNET));
	std::shared_ptr<NetworkProperties> np = std::shared_ptr<NetworkProperties>(new NetworkProperties({rtt_mean,rtt_stddev}));
	std::shared_ptr<NetworkNodeSimulator> m = std::shared_ptr<NetworkNodeSimulator>(new NetworkNodeSimulator (np, writer, n1configs, simulation_time));
	m->initialize();

	// std::shared_ptr<TCPState> client = std::shared_ptr<TCPState>(new TCPState(std::shared_ptr<TCPSegment>(new TCPSegment)));
	// client->get_current_segment()->set_destination_port(20);
	// client->get_current_segment()->set_source_port(5);
	// client->get_current_segment()->set_ipv4_pseudo_header(source, destination);

	// std::shared_ptr<TCPState> server = std::shared_ptr<TCPState>(new TCPState(std::shared_ptr<TCPSegment>(new TCPSegment)));
	// server->get_current_segment()->set_destination_port(5);
	// server->get_current_segment()->set_source_port(20);
	// server->get_current_segment()->set_ipv4_pseudo_header(destination, source);


	// m->receive_message(client, server, 0, 0);

	m->run();


	// NetworkNode a = std::get<0>(generator_1);
	// a.mac_address = {0xAC, 0xD9, 0x10, 0x43};
	// NetworkNode b = std::get<2>(generator_1);
	// b.mac_address = {0x52, 0xD3, 0xDF, 0xB4};

	// NetworkGenerator sim1(a, b, 0);

	// // NetworkNode c = {{0x11, 0x12, 0x13, 0x14, 0x15, 0x16}, {0xAC, 0xD9, 0x10, 0x43}, 53254};
	// // NetworkNode d = {{0x16, 0x15, 0x13, 0x14, 0x15, 0x16}, {0x52, 0xD3, 0xDE, 0x04}, 443};

	// // NetworkGenerator sim2(c, d, 4);

	// sim1.setup_tcp_connection();
	// sim1.simulate_tcp_connection(std::get<1>(generator_1), std::get<3>(generator_1));

	// // sim2.setup_tcp_connection();
	// // sim2.simulate_tcp_connection(7,4);
	




	// std::vector<std::tuple<uint64_t, std::shared_ptr<CommunicationProtocol>>> frames = sim1.get_trace();

	// // for (auto f : sim2.get_trace()) {
	// // 	frames.push_back(f);
	// // }

	// std::sort(frames.begin(), frames.end());

	// pcap_t *handle = pcap_open_dead(DLT_EN10MB, 1 << 16);
	// pcap_dumper_t *dumper = pcap_dump_open(handle, "./test.pcap");

	// for (auto f : frames) {
	// 	std::vector<unsigned char> protocol_data = std::get<1>(f)->header_payload_to_array();

	// 	struct pcap_pkthdr pcap_hdr;
	// 	struct timeval timestamp;
	// 	timestamp.tv_sec = 0;
	// 	timestamp.tv_usec = std::get<0>(f)*100;

	// 	pcap_hdr.caplen = protocol_data.size();
	// 	pcap_hdr.len = pcap_hdr.caplen;
	// 	pcap_hdr.ts = timestamp;

	// 	pcap_dump((u_char *)dumper, &pcap_hdr, protocol_data.data());
	// }

	// pcap_dump_close(dumper);


	return 0;
}