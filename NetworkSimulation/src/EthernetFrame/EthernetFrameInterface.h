/*
 * EthernetFrameInterface.h
 *
 *  Created on: 23 Oct 2023
 *      Author: erik
 */

#include "../MACAddress/MACAddressInterface.h"
#include "../Ethertype/EthertypeInterface.h"
#include "CommunicationProtocol.h"
#include <memory>

#ifndef ETHERNETFRAMEINTERFACE_H_
#define ETHERNETFRAMEINTERFACE_H_

class EthernetFrameInterface : public CommunicationProtocol {
public:
	virtual ~EthernetFrameInterface() = default;
	
	virtual void set_destination_address(std::shared_ptr<MACAddressInterface> destination_address) = 0;
	virtual void set_source_address(std::shared_ptr<MACAddressInterface> source_address) = 0;
	virtual void set_ethertype(std::shared_ptr<EthertypeInterface> ethertype) = 0;
	virtual std::shared_ptr<MACAddressInterface> get_destination_address() = 0;
	virtual std::shared_ptr<MACAddressInterface> get_source_address() = 0;
};

#endif /* ETHERNETFRAMEINTERFACE_H_ */
