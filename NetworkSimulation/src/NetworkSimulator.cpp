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

	m->run();

	return 0;
}