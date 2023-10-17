/*
 * MACAdressInterface.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <array>
#include <vector>
#include <string>
#include <stdexcept>

#ifndef MACADDRESSINTERFACE_H_
#define MACADDRESSINTERFACE_H_

class MACAddressInterface {
private:
	std::vector<unsigned char> address;
public:
	virtual bool is_valid_mac_address(std::string address) = 0;
	virtual void set_address(std::vector<unsigned char> address) = 0;
	virtual std::vector<unsigned char> get_address() = 0;
};



#endif /* MACADDRESSINTERFACE_H_ */
