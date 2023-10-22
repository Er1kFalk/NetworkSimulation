#include "IPv4Address.h"
#include <stdexcept>

const int IPv4Address::address_size = 4;

void IPv4Address::set_address(std::vector<unsigned char> address) {
    if (address.size() != address_size) {
        throw std::invalid_argument("Address not the right size. Should be 4-bytes.");
    }

    this->address = address;
}