/*
 * MACAdress.cpp
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "MACAdress.h"
#include "../ArrayUtils/ArrayUtils.h"

void MACAdress::set_address(std::array<unsigned char, 6> address) {
	ArrayUtils<unsigned char, 6> arrutil;
	this->address = arrutil.to_vector(address);
}
