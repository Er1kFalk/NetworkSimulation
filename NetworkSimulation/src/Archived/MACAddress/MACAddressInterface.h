/*
 * MACAdressInterface.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <array>
#include <string>
#include <stdexcept>

#ifndef MACADDRESSINTERFACE_H_
#define MACADDRESSINTERFACE_H_

class MACAddressInterface {
public:
	virtual bool is_valid_mac_address(std::string address) = 0;
	virtual void set_address(std::array<unsigned char, 6> address) = 0;
	virtual std::array<unsigned char, 6> get_address() = 0;
};



#endif /* MACADDRESSINTERFACE_H_ */
