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

class EthernetFrame : public EthernetFrameInterface {
private:
	static inline const uint8_t DESTINATION_ADDRESS_SIZE = 6;
	static inline const uint8_t SOURCE_ADDRESS_SIZE = 6;
	static inline const uint8_t ETHERTYPE_SIZE = 2;

	MACAddressInterface *destination_address;
	MACAddressInterface *source_address;
	EthertypeInterface *ethertype;

public:
	~EthernetFrame() {}

	

	void set_destination_address(MACAddressInterface *destination_address) override;

	void set_source_address(MACAddressInterface *source_address) override;

	void set_ethertype(EthertypeInterface *ethertype) override {
		this->ethertype = ethertype;
	}

	MACAddressInterface* get_destination_address() override {
		return destination_address;
	}

	MACAddressInterface* get_source_address() override {
		return source_address;
	}

	EthernetFrame(MACAddressInterface *destination_address, MACAddressInterface *source_address, EthertypeInterface *ethertype, CommunicationProtocol *payload) {
		set_destination_address(destination_address);
		set_source_address(source_address);
		set_ethertype(ethertype);
		set_payload(payload);
	}

	std::vector<unsigned char> to_array() override;

};



#endif /* ETHERNETFRAME_H_ */
