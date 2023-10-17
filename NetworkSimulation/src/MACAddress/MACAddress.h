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
	std::vector<unsigned char> address;
	static const int address_char_length;
	static const int address_octet_length;
public:
	bool is_valid_mac_address(std::string address);
	void set_address(std::vector<unsigned char> address) override;
	std::vector<unsigned char> get_address() override {
		return address;
	}
};



#endif /* MACADDRESS_H_ */
