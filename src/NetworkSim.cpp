//============================================================================
// Name        : NetworkSim.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pcap.h>
#include "PCAPReader.h"


int main() {
	char* filepath = "./src/test_trace.pcapng";
	try {
		count_packets(filepath);
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}
