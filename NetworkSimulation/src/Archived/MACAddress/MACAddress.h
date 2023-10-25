/*
 * MACAdress.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "MACAddressInterface.h"

#ifndef MACADDRESS_H_
#define MACADDRESS_H_

class MACAddress : public MACAddressInterface {
private:
	std::array<unsigned char, 6> address;
	static const int address_char_length;
	static const int address_octet_length;
public:
	MACAddress(std::array<unsigned char, 6> address) {
		this->address = address;
	}

	bool is_valid_mac_address(std::string address);
	void set_address(std::array<unsigned char, 6> address) override {this->address = address;}
	std::array<unsigned char, 6> get_address() override {return address;}
};



#endif /* MACADDRESS_H_ */
