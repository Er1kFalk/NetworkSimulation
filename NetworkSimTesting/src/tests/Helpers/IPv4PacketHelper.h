/*
 * IPv4PacketHelper.h
 *
 *  Created on: 25 Oct 2023
 *      Author: erik
 */

#include "IPv4Packet/IPv4Packet.h"
#include <memory>

#ifndef IPV4PACKETHELPER_H_
#define IPV4PACKETHELPER_H_

class IPv4PacketHelper {
public:
	std::unique_ptr<IPv4PacketInterface> get_stdpacket() {
		return std::unique_ptr<IPv4PacketInterface> (new IPv4Packet(
				2, // dscp
				0, // ecn
				0,
				false,
				false,
				0,
				64,
				0x01,
				{0x01, 0x02, 0x03, 0x04},
				{0x01, 0x02, 0x03, 0x04},
				std::shared_ptr<CommunicationProtocol>(new Data({0x11, 0x12, 0x13}))
			));	
	}
    
};

#endif /* IPV4PACKETHELPER_H_ */
