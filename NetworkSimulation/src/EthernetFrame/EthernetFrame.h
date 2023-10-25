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
#include "../CommunicationProtocol.h"
#include "EthernetFrameInterface.h"
#include <cassert>
#include <memory>

class EthernetFrame : public EthernetFrameInterface {
private:
	static inline const uint8_t DESTINATION_ADDRESS_SIZE = 6;
	static inline const uint8_t SOURCE_ADDRESS_SIZE = 6;
	static inline const uint8_t ETHERTYPE_SIZE = 2;

	std::array<unsigned char, 6> destination_address;
	std::array<unsigned char, 6> source_address;
	std::array<unsigned char, 2> ethertype;

public:
	~EthernetFrame() {}

	

	void set_destination_address(std::array<unsigned char, 6> destination_address) override {this->destination_address = destination_address;}
	void set_source_address(std::array<unsigned char, 6> source_address) override {this->source_address = source_address;}
	void set_ethertype(std::array<unsigned char, 2> ethertype) override {this->ethertype = ethertype;}

	std::array<unsigned char, 6> get_destination_address() override {return this->destination_address;}
	std::array<unsigned char, 6> get_source_address() override {return source_address;}

	EthernetFrame(std::array<unsigned char, 6> destination_address, std::array<unsigned char, 6> source_address, std::array<unsigned char, 2> ethertype, std::shared_ptr<CommunicationProtocol> payload = nullptr) {
		this->destination_address = destination_address;
		this->source_address = source_address;
		this->ethertype = ethertype;
		set_payload(payload);
	}

	std::vector<unsigned char> to_array() override;

};



#endif /* ETHERNETFRAME_H_ */
