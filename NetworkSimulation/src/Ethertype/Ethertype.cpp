/*
 * Ethertype.cpp
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */
#include "Ethertype.h"
#include "StringUtils/StringUtils.h"
#include <stdexcept>
#include <sstream>

const std::vector<std::pair<std::string, std::vector<unsigned char>>> Ethertype::ethertype_common_values = {
	{"ipv4", {0x08, 0x00}},
	{"arp", {0x08, 0x06}},
	{"ipv6", {0x86, 0xDD}}
};

void Ethertype::set_ethertype(std::vector<unsigned char> ethertype) {
	if (ethertype.size() != this->get_octet_length()) {
		std::ostringstream err;
		err << "Ethertype should be " << this->get_octet_length() << " octets, but was " << ethertype.size() << " octets";
		throw std::invalid_argument(err.str());
	} else {
		this->ethertype = ethertype;
	}
}

void Ethertype::set_ethertype(std::string ethertype) {
	std::string ethertype_to_lower = StringUtils::to_lower(ethertype);
	auto it = ethertype_common_values.begin();
	while (it != ethertype_common_values.end()) {
		if (it->first.compare(ethertype_to_lower) == 0) {
			this->ethertype = it->second;
			break;
		}
		it++;
	}
	// if we have looked through all conversions and found none, throw error
	if (it == ethertype_common_values.end()) {
		std::string err = "Conversion from string '" + ethertype + "' to ethertype value does not exist.";
		throw std::invalid_argument(err);
	}
}