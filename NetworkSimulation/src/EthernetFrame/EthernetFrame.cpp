//============================================================================
// Name        : EthernetFrame.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <pcap.h>
#include <zlib.h>
#include <array>
#include <vector>
#include "EthernetFrame.h"
#include <stdexcept>
#include <algorithm>
#include <list>

std::vector<unsigned char> EthernetFrame::header_to_array() {
	std::vector<unsigned char> header;

	auto add_to_header = [&header](unsigned char elem) -> void {
		header.push_back(elem);
	};

	std::for_each(this->destination_address.begin(), this->destination_address.end(), add_to_header);
	std::for_each(this->source_address.begin(), this->source_address.end(), add_to_header);
	std::for_each(this->ethertype.begin(), this->ethertype.end(), add_to_header);

		
	return header;
}

std::vector<unsigned char> EthernetFrame::header_payload_to_array() {
    std::vector<unsigned char> header_payload = this->header_to_array();
    
    std::shared_ptr<CommunicationProtocol> it = this->payload;
    while (it != nullptr) {
		for (unsigned char c : it->header_to_array()) {
            header_payload.push_back(c);
        }
		it = it->get_payload();
	}

    return header_payload;
}
