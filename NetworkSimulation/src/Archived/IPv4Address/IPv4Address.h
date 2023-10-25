/*
 * IPv4Address.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include "IPv4AddressInterface.h"

#ifndef IPV4ADDRESS_H_
#define IPV4ADDRESS_H_

class IPv4Address : public IPv4AddressInterface {
private:
    std::array<unsigned char, 4> address;
public:
    void set_address(std::array<unsigned char, 4>  address) override {this->address = address;}
    std::array<unsigned char, 4> get_address() override {return address;}

    IPv4Address(std::array<unsigned char, 4> address) {
        set_address(address);
    }
};


#endif /*IPV4ADDRESS_H_*/