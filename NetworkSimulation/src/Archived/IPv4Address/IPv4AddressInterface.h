/*
 * IPv4AddressInterface.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include <array>

#ifndef IPV4ADDRESSINTERFACE_H_
#define IPV4ADDRESSINTERFACE_H_

class IPv4AddressInterface {
public:
    virtual void set_address(std::array<unsigned char, 4>  address) = 0;
    virtual std::array<unsigned char, 4> get_address() = 0;
};

#endif /*IPV4ADDRESSINTERFACE_H_*/