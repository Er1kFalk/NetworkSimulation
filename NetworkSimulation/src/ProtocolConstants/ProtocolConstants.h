/*
 * ProtocolConstants.h
 *
 *  Created on: 24 Oct 2023
 *      Author: erik
 */

#include <vector>

#ifndef PROTOCOLCONSTANTS_H_
#define PROTOCOLCONSTANTS_H_


namespace EthertypeConstants {
    const std::array<unsigned char, 2> IPv4 = {0x08, 0x00};
    const std::array<unsigned char, 2> IPv6 = {0x86, 0xDD};
    const std::array<unsigned char, 2> ARP = {0x08, 0x06};
}

#endif /* PROTOCOLCONSTANTS_H_ */
