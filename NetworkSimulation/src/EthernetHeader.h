/*
 * EthernetHeader.h
 *
 *  Created on: 29 Sept 2023
 *      Author: erik
 */

#ifndef ETHERNETHEADER_H_
#define ETHERNETHEADER_H_

#include <stdint.h>
#include <map>
#include <string>
#include "Ethertype/Ethertype.h"
#include "Ethertype/EthertypeInterface.h"
#include "CommunicationProtocol.h"
#include "LANProtocol.h"

class EthernetFrame : public LANProtocol {
private:
	static inline const uint8_t DESTINATION_ADDRESS_SIZE = 6;
	static inline const uint8_t SOURCE_ADDRESS_SIZE = 6;
	static inline const uint8_t ETHERTYPE_SIZE = 2;

	EthertypeInterface *ethertype;

public:
	~EthernetFrame() {}

	void set_destination_address(MACAddressInterface *destination_address) override;

	void set_source_address(MACAddressInterface *source_address) override;

	void set_ethertype(EthertypeInterface *ethertype) {
		this->ethertype = ethertype;
	}

	MACAddressInterface* get_destination_address() override {
		return destination_address;
	}

	MACAddressInterface* get_source_address() override {
		return source_address;
	}

	std::vector<std::vector<unsigned char>> to_array() override;

};



#endif /* ETHERNETHEADER_H_ */
