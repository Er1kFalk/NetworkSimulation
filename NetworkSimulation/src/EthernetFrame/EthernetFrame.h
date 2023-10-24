/*
 * EthernetFrame.h
 *
 *  Created on: 29 Sept 2023
 *      Author: erik
 */

#ifndef ETHERNETFRAME_H_
#define ETHERNETFRAME_H_

#include <stdint.h>
#include <map>
#include <string>
#include "Ethertype/Ethertype.h"
#include "Ethertype/EthertypeInterface.h"
#include "../CommunicationProtocol.h"
#include "EthernetFrameInterface.h"
#include <cassert>
#include <memory>

class EthernetFrame : public EthernetFrameInterface {
private:
	static inline const uint8_t DESTINATION_ADDRESS_SIZE = 6;
	static inline const uint8_t SOURCE_ADDRESS_SIZE = 6;
	static inline const uint8_t ETHERTYPE_SIZE = 2;

	std::shared_ptr<MACAddressInterface> destination_address;
	std::shared_ptr<MACAddressInterface> source_address;
	std::shared_ptr<EthertypeInterface> ethertype;

public:
	~EthernetFrame() {}

	

	void set_destination_address(std::shared_ptr<MACAddressInterface> destination_address) override;

	void set_source_address(std::shared_ptr<MACAddressInterface> source_address) override;

	void set_ethertype(std::shared_ptr<EthertypeInterface> ethertype) override {
		this->ethertype = ethertype;
	}

	std::shared_ptr<MACAddressInterface> get_destination_address() override {
		return this->destination_address;
	}

	std::shared_ptr<MACAddressInterface> get_source_address() override {
		return source_address;
	}

	EthernetFrame(std::shared_ptr<MACAddressInterface> destination_address, std::shared_ptr<MACAddressInterface> source_address, std::shared_ptr<EthertypeInterface> ethertype, std::shared_ptr<CommunicationProtocol> payload) {
		this->destination_address = destination_address;
		this->source_address = source_address;
		this->ethertype = ethertype;
		set_payload(payload);
	}

	std::vector<unsigned char> to_array() override;

};



#endif /* ETHERNETFRAME_H_ */
