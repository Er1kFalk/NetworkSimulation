/*
 * IPv4AddressInterface.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include <vector>

#ifndef IPV4ADDRESSINTERFACE_H_
#define IPV4ADDRESSINTERFACE_H_

class IPv4AddressInterface {
public:
    virtual void set_address(std::vector<unsigned char> address) = 0;
    virtual std::vector<unsigned char> get_address() = 0;
};

#endif /*IPV4ADDRESSINTERFACE_H_*/