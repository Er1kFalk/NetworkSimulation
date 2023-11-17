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

struct defaultPacketArgs{
	unsigned char dscp = 0;
	unsigned char ecn = 0;
	int identfication_id = 0;
	bool df = false;
	bool mf = false;
	unsigned int offset = 0;
	unsigned char time_to_live = 64;
	unsigned char p = 0x01;
	std::array<unsigned char, 4> destination_address = {0x01, 0x02, 0x03, 0x04};
	std::array<unsigned char, 4> source_address = {0x01, 0x02, 0x03, 0x04};
	std::vector<unsigned char> options = {};
	std::shared_ptr<CommunicationProtocol> payload = std::shared_ptr<CommunicationProtocol>(new Data({0x11, 0x12, 0x13}));
};

class IPv4PacketHelper {
public:
	std::unique_ptr<IPv4PacketInterface> get_stdpacket(defaultPacketArgs args
	) {
		return std::unique_ptr<IPv4PacketInterface> (new IPv4Packet(
				args.dscp, // dscp
				args.ecn, // ecn
				args.identfication_id,
				args.df,
				args.mf,
				args.offset,
				args.time_to_live,
				args.p,
				args.destination_address,
				args.source_address,
				args.options,
				args.payload
			));	
	}
    
};

#endif /* IPV4PACKETHELPER_H_ */
