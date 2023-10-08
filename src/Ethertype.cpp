/*
 * Ethertype.cpp
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */
#include "Ethertype.h"
#include "StringUtils/StringUtils.h"
#include <stdexcept>

const std::map<std::string, std::vector<unsigned char>> Ethertype::ethertype_common_values = {
	{"ipv4", {0x08, 0x00}},
	{"arp", {0x08, 0x06}},
	{"ipv6", {0x86, 0xDD}}
};

void Ethertype::set_ethertype(std::string ethertype) {
	StringUtils strutil;
	ethertype = strutil.to_lower(ethertype);
	auto i = this->ethertype_common_values.find(ethertype);
	if (i != this->ethertype_common_values.end()) {
		this->ethertype = i->second;
	} else {
		throw std::invalid_argument("Ethertype not in the ethertype_common_values table.");
	}
}

std::string Ethertype::to_string() {
	for (auto i : ethertype_common_values) {
		if (i.second == ethertype) {
			return i.first;
		}
	}

	return "no string conversion available";
}
