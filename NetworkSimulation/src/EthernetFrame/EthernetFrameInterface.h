/*
 * EthernetFrameInterface.h
 *
 *  Created on: 23 Oct 2023
 *      Author: erik
 */

#include "../CommunicationProtocol.h"
#include <memory>
#include <stdint.h>

#ifndef ETHERNETFRAMEINTERFACE_H_
#define ETHERNETFRAMEINTERFACE_H_

class EthernetFrameInterface : public CommunicationProtocol {
public:
	virtual ~EthernetFrameInterface() = default;
	
	virtual void set_destination_address(std::array<unsigned char, 6> destination_address) = 0;
	virtual void set_source_address(std::array<unsigned char, 6> source_address) = 0;
	virtual void set_ethertype(std::array<unsigned char, 2> ethertype) = 0;
	virtual std::array<unsigned char, 6> get_destination_address() = 0;
	virtual std::array<unsigned char, 6> get_source_address() = 0;
	virtual std::shared_ptr<EthernetFrameInterface> copy() = 0;
};

#endif /* ETHERNETFRAMEINTERFACE_H_ */
