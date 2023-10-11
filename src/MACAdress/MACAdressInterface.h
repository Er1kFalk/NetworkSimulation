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

#ifndef MACADRESSINTERFACE_H_
#define MACADRESSINTERFACE_H_

class MACAdressInterface {
private:
	std::vector<unsigned char> address;
public:
	virtual bool is_valid_mac_address(std::string address) = 0;
	virtual void set_address(std::array<unsigned char, 6> address) = 0;
	virtual void set_address(std::string address) = 0;
	virtual std::vector<unsigned char> get_address() = 0;
};



#endif /* MACADRESSINTERFACE_H_ */
