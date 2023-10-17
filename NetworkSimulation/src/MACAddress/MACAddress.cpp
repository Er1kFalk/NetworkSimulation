/*
 * MACAdress.cpp
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "MACAddress.h"
#include "../ArrayUtils/ArrayUtils.h"
#include "../StringUtils/StringUtils.h"
#include <sstream>
#include <stdexcept>

const int MACAddress::address_char_length = 17;
const int MACAddress::address_octet_length = 6;

bool MACAddress::is_valid_mac_address(std::string address) {
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

/*
PRE: ADDRESS VECTOR HAS 6 ELEMENTS
POST: THE ADDRESS IN MACADDRESS IS SET TO THE ADDRESS USER INPUTTED
*/
void MACAddress::set_address(std::vector<unsigned char> address) {
	if (address.size() != address_octet_length) {
		throw std::invalid_argument("Address must have 6 octets (elements).");
	}
	this->address = address;
}