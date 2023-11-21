#include "EthernetFrame/EthernetFrameInterface.h"
#include "EthernetFrame/EthernetFrame.h"
#include "IPv4Packet/IPv4PacketInterface.h"
#include "IPv4Packet/IPv4Packet.h"
#include "ProtocolConstants/ProtocolConstants.h"
#include "TCPSegment/TCPSegment.h"
#include "ArrayUtils/ArrayUtils.h"
#include "ProtocolUtils/ProtocolUtils.h"
#include "Simulator/NetworkNodeSimulator/NetworkNodeSimulator.h"
#include "Simulator/NetworkProperties.h"
#include "TCPSegment/TCPSegment.h"
#include "PCAPWriter/PCAPWriter.h"

#include <bits/stdc++.h>

#include <iostream>

#include <tuple>

#include <cstdlib>
#include <math.h>

#include <pcap/pcap.h>
#include "TCPConnection/TCPConnection.h"
#include "Simulator/TCPSimulator/TCPEvent.h"

struct NetworkNode {
	std::array<unsigned char, 6> mac_address;
	std::array<unsigned char, 4> ip_address;
	uint16_t source_port;
};

// class NetworkGenerator {
// 	NetworkNode client, server;

// 	uint64_t timestamp;
// 	std::shared_ptr<TCPConnection> tcp_connection;

// 	std::vector<std::tuple<uint64_t, std::shared_ptr<CommunicationProtocol>>> trace;
// public:
// 	NetworkGenerator(NetworkNode client, NetworkNode server, uint64_t timestamp) {
// 		this->client = client;
// 		this->server = server;
// 		this->timestamp = timestamp;

// 	}

// 	std::shared_ptr<EthernetFrameInterface> ethernet_base_frame_client() {
// 		return std::shared_ptr<EthernetFrameInterface>(new EthernetFrame(
// 			client.mac_address,
// 			server.mac_address,
// 			EthertypeConstants::IPv4
// 		));
// 	}

// 	std::shared_ptr<EthernetFrameInterface> ethernet_base_frame_server() {
// 		return std::shared_ptr<EthernetFrameInterface>(new EthernetFrame(
// 			server.mac_address,
// 			client.mac_address,
// 			EthertypeConstants::IPv4
// 		));
// 	}

// 	std::shared_ptr<IPv4PacketInterface> ip_base_packet_client(unsigned char protocol) {
// 		return std::shared_ptr<IPv4PacketInterface>(new IPv4Packet(
// 				0, // dscp
// 				0, // ecn
// 				0, // identification ID
// 				false, // df
// 				false, // mf
// 				0, // offset
// 				64, // ttl
// 				protocol, // protocol
// 				client.ip_address,
// 				server.ip_address,
// 				{},
// 				nullptr
// 			)
// 		);
// 	}

// 	std::shared_ptr<IPv4PacketInterface> ip_base_packet_server(unsigned char protocol) {
// 		return std::shared_ptr<IPv4PacketInterface>(new IPv4Packet(
// 				0, // dscp
// 				0, // ecn
// 				0, // identification ID
// 				false, // df
// 				false, // mf
// 				0, // offset
// 				64, // ttl
// 				protocol, // protocol
// 				server.ip_address,
// 				client.ip_address,
// 				{},
// 				nullptr
// 			)
// 		);
// 	}

// 	void setup_tcp_connection() {
// 		tcp_connection = std::shared_ptr<TCPConnection>(new TCPConnection(client.source_port, server.source_port, timestamp));
// 	}

// 	void simulate_tcp_connection(int dataout, int datain) {
// 		tcp_connection->three_way_handshake();
// 		tcp_connection->send_data(dataout, datain);
// 		std::vector<std::tuple<uint64_t, std::shared_ptr<TCPSegmentInterface>>> tcp_trace_client = tcp_connection->get_segment_trace_client();
// 		std::vector<std::tuple<uint64_t, std::shared_ptr<TCPSegmentInterface>>> tcp_trace_server = tcp_connection->get_segment_trace_server();

// 		std::cout << std::hex << (int) std::get<1>(tcp_trace_client[0])->header_to_array()[13] << std::endl;

// 		for (auto t : tcp_trace_client) {
// 			std::shared_ptr<EthernetFrameInterface> ethernetframe (new EthernetFrame(server.mac_address, client.mac_address, EthertypeConstants::IPv4));

// 			std::shared_ptr<CommunicationProtocol> protocol_stack = ProtocolUtils::build_protocol_stack_from_vector({ethernet_base_frame_client(), ip_base_packet_client(0x06), std::get<1>(t)});
// 			this->trace.push_back({std::get<0>(t), protocol_stack});
// 		}

// 		for (auto t : tcp_trace_server) {

// 			std::shared_ptr<CommunicationProtocol> protocol_stack = ProtocolUtils::build_protocol_stack_from_vector({ethernet_base_frame_server(), ip_base_packet_server(0x06), std::get<1>(t)});
// 			this->trace.push_back({std::get<0>(t), protocol_stack});
// 		}
// 	}

// 	std::vector<std::tuple<uint64_t, std::shared_ptr<CommunicationProtocol>>> get_trace() {return trace;}
// };

// std::array<unsigned char, 4> ip_address_string_to_vec(std::string ip) {
// 	std::string ip_block = "";
// 	std::array<unsigned char, 4> vec_ip = {};
// 	int i = 0;
// 	for (unsigned char c : ip) {
// 		if (c>=48 && c <=57) { // c is a nr
// 			ip_block += c;
// 		} else if (c == '.') {
// 			vec_ip[i] = std::stoi(ip_block);
// 			i++;
// 			ip_block = "";
// 			continue;
// 		} else {
// 			throw std::invalid_argument("Not a valid ip");
// 		}
// 	}
// 	vec_ip[i] = std::stoi(ip_block);
// 	return vec_ip;
// }

// std::tuple<NetworkNode, int, NetworkNode, int> read_definition(std::string filepath) {
// 	boost::property_tree::ptree root;
// 	boost::property_tree::read_json(filepath, root);

// 	NetworkNode client, server;
// 	int clientpackets_sent, serverpackets_sent;

// 	if (root.get<bool>("NODE_1.INIT_CONNECTION")) {
// 		client.ip_address = ip_address_string_to_vec(root.get<std::string>("NODE_1.IP_ADDRESS"));
// 		if (root.get<std::string>("NODE_1.TCP_INFO.SOURCE_PORT").compare("random") == 0) {
// 			client.source_port = rand() % 65535;
// 		} else {
// 			client.source_port = root.get<int>("NODE_1.TCP_INFO.SOURCE_PORT");
// 		}
// 		clientpackets_sent = root.get<int>("NODE_1.TCP_INFO.PACKETS_SENT");

// 		server.ip_address = ip_address_string_to_vec(root.get<std::string>("NODE_2.IP_ADDRESS"));
// 		if (root.get<std::string>("NODE_2.TCP_INFO.SOURCE_PORT").compare("random") == 0) {
// 			server.source_port = rand() % 65535;
// 		} else {
// 			server.source_port = root.get<int>("NODE_2.TCP_INFO.SOURCE_PORT");
// 		}
// 		serverpackets_sent = root.get<int>("NODE_2.TCP_INFO.PACKETS_SENT");
// 	} else {
// 		server.ip_address = ip_address_string_to_vec(root.get<std::string>("NODE_1.IP_ADDRESS"));
// 		if (root.get<std::string>("NODE_1.TCP_INFO.SOURCE_PORT").compare("random") == 0) {
// 			server.source_port = rand() % 65535;
// 		} else {
// 			server.source_port = root.get<int>("NODE_1.TCP_INFO.SOURCE_PORT");
// 		}

// 		client.ip_address = ip_address_string_to_vec(root.get<std::string>("NODE_2.IP_ADDRESS"));
// 		if (root.get<std::string>("NODE_2.TCP_INFO.SOURCE_PORT").compare("random") == 0) {
// 			client.source_port = rand() % 65535;
// 		} else {
// 			client.source_port = root.get<int>("NODE_2.TCP_INFO.SOURCE_PORT");
// 		}
// 		clientpackets_sent = root.get<int>("NODE_2.TCP_INFO.PACKETS_SENT");
// 	}
// 	return {client, clientpackets_sent, server, serverpackets_sent};
// }

int main(int argc, char *argv[]) {
	
	// std::tuple<NetworkNode, int, NetworkNode, int> generator_1 = read_definition("../SimulatorConfig/simulator1.json");
	// int x = 0;
	// std::cout << "Hello World" << std::endl;
	// std::cout << "Hello No" << std::endl;

	std::vector<unsigned char> source = {0x01, 0x02, 0x03, 0x04};
	std::vector<unsigned char> destination = {0x01, 0x02, 0x03, 0x04};

	auto n1configs = std::shared_ptr<ConfigReader>(new ConfigReader({"../SimulatorConfig/"}));

	auto writer = std::shared_ptr<PCAPWriter>(new PCAPWriter("./test.pcap", wayne::PCAP::linkTypes::LINKTYPE_ETHERNET));
	std::shared_ptr<NetworkProperties> np = std::shared_ptr<NetworkProperties>(new NetworkProperties({1,2}, NetworkLayer::IPv4));
	std::shared_ptr<NetworkNodeSimulator> m = std::shared_ptr<NetworkNodeSimulator>(new NetworkNodeSimulator (np, writer, n1configs, 50));
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

	m->initialize();

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