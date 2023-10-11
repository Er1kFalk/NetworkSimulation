/*
 * MACAdress.cpp
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "MACAdress.h"
#include "../ArrayUtils/ArrayUtils.h"
#include "../StringUtils/StringUtils.h"

const int MACAdress::address_char_length = 17;

bool MACAdress::is_valid_mac_address(std::string address) {
	if (address.length() != address_char_length) {
		return false;
	}
	for (std::string::size_type i = 0; i < address.length(); i++) {
		char c = (char) address[i];
		if ((i+1) % 3 == 0) {
			if (c != (char) ':') { // every 3rd char is a :
				return false;
			}
		} else { // the others are hex symbols
			if (!StringUtils::is_hex_symbol(c)) {
				return false;
			}
		}
	}
	return true;
}

void MACAdress::set_address(std::array<unsigned char, 6> address) {
	this->address = ArrayUtils::to_vector(address);
}

void MACAdress::set_address(std::string address) {
	if (!is_valid_mac_address(address)) {
		throw std::invalid_argument("Invalid MAC address specified. Format should be ff:ff:ff:ff.");
	}
}
