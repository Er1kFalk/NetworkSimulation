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

// const std::vector<std::pair<ProtocolConstants::EthertypeName, std::array<unsigned char, 2>>> Ethertype::ethertype_common_values = {
// 	{ProtocolConstants::IPv4, {0x08, 0x00}},
// 	{ProtocolConstants::IPv6, {0x86, 0xDD}},
// 	{ProtocolConstants::ARP, {0x08, 0x06}}
// };

// Ethertype::Ethertype(ProtocolConstants::EthertypeName ethertype) {
// 	for (std::pair<ProtocolConstants::EthertypeName, std::array<unsigned char, 2>> e : ethertype_common_values) {
// 		if (e.first == ethertype) {
// 			this->ethertype = e.second;
// 		}
// 	}
// }

// void Ethertype::set_ethertype(ProtocolConstants::EthertypeName ethertype) {
// 	for (std::pair<ProtocolConstants::EthertypeName, std::array<unsigned char, 2>> e : ethertype_common_values) {
// 		if (e.first == ethertype) {
// 			this->ethertype = e.second;
// 		}
// 	}

// 	// auto it = ethertype_common_values.begin();
// 	// while (it != ethertype_common_values.end()) {
// 	// 	if (it->first.compare(ethertype_to_lower) == 0) {
// 	// 		this->ethertype = it->second;
// 	// 		break;
// 	// 	}
// 	// 	it++;
// 	// }
// 	// // if we have looked through all conversions and found none, throw error
// 	// if (it == ethertype_common_values.end()) {
// 	// 	std::string err = "Conversion from string '" + ethertype + "' to ethertype value does not exist.";
// 	// 	throw std::invalid_argument(err);
// 	// }
// }