////============================================================================
//// Name        : NetworkSim.cpp
//// Author      :
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <iostream>
//#include <pcap.h>
//#include <stdexcept>
//
//pcap_t* open_pcap_file(char* file_path) {
//	char errbuf[PCAP_ERRBUF_SIZE]; // mandatory buffer for storing potential error when reading pcap file
//
//	pcap_t* file_pcap = pcap_open_offline(file_path, errbuf); // open pcapfile
//
//	if (file_pcap == NULL) {
//		throw std::invalid_argument(errbuf);
//	}
//
//	return file_pcap;
//}
//
//void count_packets(char* filepath) {
//	pcap_t* file_pcap;
//	char errbuf[PCAP_ERRBUF_SIZE]; // mandatory buffer for storing potential error when reading pcap file
//	struct pcap_pkthdr header;
//	const uint8_t *packet;
//
//	try{
//		file_pcap = open_pcap_file(filepath); // open pcapfile
//	}
//	catch (std::invalid_argument& e) { // if invalid argument is given, caller has to handle
//		throw;
//	}
//	// pcap_next returns null if no packets  => loop will exit
//	int packetCount = 1;
//	while (packet = pcap_next(file_pcap, &header)) {
//		std::cout << "received packet nr " << packetCount++ << std::endl;
//	}
//
//	pcap_close(file_pcap);
//}
