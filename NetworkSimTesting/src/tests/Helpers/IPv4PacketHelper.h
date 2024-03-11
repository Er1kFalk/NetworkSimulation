/*
 * IPv4PacketHelper.h
 *
 *  Created on: 25 Oct 2023
 *      Author: erik
 */

#include "../../../../NetworkSimulation/src/HeaderGenerators/IPv4Packet/IPv4Packet.h"
#include "../../../../NetworkSimulation/src/HeaderGenerators/Data/Data.h"
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
	std::vector<unsigned char> destination_address = {0x01, 0x02, 0x03, 0x04};
	std::vector<unsigned char> source_address = {0x01, 0x02, 0x03, 0x04};
	std::vector<unsigned char> options = {};
	std::shared_ptr<CommunicationProtocol> payload = std::shared_ptr<CommunicationProtocol>(new Data({0x11, 0x12, 0x13}));
};

class IPv4PacketHelper {
public:
    std::shared_ptr<IPv4PacketInterface> get_stdpacket(defaultPacketArgs args
	) {

        std::shared_ptr<IPv4PacketInterface> p = std::shared_ptr<IPv4PacketInterface>(new IPv4Packet());
		p->set_version();
		p->set_dscp(args.dscp);
		p->set_ecn(args.ecn);
		p->set_identification(args.identfication_id);
		p->set_df_flag(args.df);
		p->set_mf_flag(args.mf);
		p->set_fragment_offset(args.offset);
		p->set_time_to_live(args.time_to_live);
		p->set_protocol(args.p);
		p->set_destination(args.destination_address);
		p->set_source(args.source_address);
		p->set_options(args.options);
		p->set_payload(args.payload);

		return p;
	}
    
};

#endif /* IPV4PACKETHELPER_H_ */
