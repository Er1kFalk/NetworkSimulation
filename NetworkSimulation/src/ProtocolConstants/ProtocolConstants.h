/*
 * ProtocolConstants.h
 *
 *  Created on: 24 Oct 2023
 *      Author: erik
 */

#include <vector>
#include <stdint.h>

#ifndef PROTOCOLCONSTANTS_H_
#define PROTOCOLCONSTANTS_H_


namespace EthertypeConstants {
    const std::array<unsigned char, 2> IPv4 = {0x08, 0x00};
    const std::array<unsigned char, 2> IPv6 = {0x86, 0xDD};
    const std::array<unsigned char, 2> ARP = {0x08, 0x06};
}

namespace IPv4Constants {
    namespace BoundaryConstants{
        const unsigned char DSCP_MIN = 0;
        const unsigned char DSCP_MAX = 63;
        const unsigned char ECN_MIN = 0;
        const unsigned char ECN_MAX = 3;
        const uint16_t FRAGMENT_OFFSET_MAX = 8191;
        const uint16_t FRAGMENT_OFFSET_MIN = 0;
    }
}

#endif /* PROTOCOLCONSTANTS_H_ */
