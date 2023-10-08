/*
 * MACAdressInterface.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <array>
#include <vector>

#ifndef MACADRESSINTERFACE_H_
#define MACADRESSINTERFACE_H_

class MACAdressInterface {
private:
	std::vector<unsigned char> address;
public:
	virtual void set_address(std::array<unsigned char, 6> address) = 0;
	virtual std::vector<unsigned char> get_address() = 0;
};



#endif /* MACADRESSINTERFACE_H_ */
