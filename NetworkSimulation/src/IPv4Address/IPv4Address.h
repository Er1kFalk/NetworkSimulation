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
    std::vector<unsigned char> address;
    static const int address_size;
public:
    void set_address(std::vector<unsigned char> address) override;
    std::vector<unsigned char> get_address() override {
        return address;
    }
};


#endif /*IPV4ADDRESS_H_*/