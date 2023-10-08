/*
 * MACAdress.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "MACAdressInterface.h"

#ifndef MACADRESS_H_
#define MACADRESS_H_

class MACAdress : public MACAdressInterface {
private:
	std::vector<unsigned char> address;
public:
	void set_address(std::array<unsigned char, 6> address) override;
	std::vector<unsigned char> get_address() override {
		return address;
	}
};



#endif /* MACADRESS_H_ */
