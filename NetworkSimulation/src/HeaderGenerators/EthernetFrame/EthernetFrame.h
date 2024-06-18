/*
 * EthernetFrame.h
 *
 *  Created on: 29 Sept 2023
 *      Author: erik
 */

#ifndef ETHERNETFRAME_H_
#define ETHERNETFRAME_H_

#include <stdint.h>
#include "EthernetFrameInterface.h"
#include <array>

class EthernetFrame : public EthernetFrameInterface {
private:
	static inline const uint8_t DESTINATION_ADDRESS_SIZE = 6;
	static inline const uint8_t SOURCE_ADDRESS_SIZE = 6;
	static inline const uint8_t ETHERTYPE_SIZE = 2;

	std::array<unsigned char, 6> destination_address;
	std::array<unsigned char, 6> source_address;
	std::array<unsigned char, 2> ethertype;

	std::shared_ptr<CommunicationProtocol> payload;

public:
	~EthernetFrame() {}

	

	void set_destination_address(std::array<unsigned char, 6> destination_address) override {this->destination_address = destination_address;}
	void set_source_address(std::array<unsigned char, 6> source_address) override {this->source_address = source_address;}
	void set_ethertype(std::array<unsigned char, 2> ethertype) override {this->ethertype = ethertype;}

	std::array<unsigned char, 6> get_destination_address() override {return this->destination_address;}
	std::array<unsigned char, 6> get_source_address() override {return source_address;}

	EthernetFrame() {
		this->destination_address = {0, 0, 0, 0, 0, 0};
		this->source_address = {0, 0, 0, 0, 0, 0};
		this->ethertype = {0, 0};
		this->payload = nullptr;
	}

	std::vector<unsigned char> header_to_array() override;
	std::vector<unsigned char> header_payload_to_array() override;

	void set_payload(std::shared_ptr<CommunicationProtocol> payload) override {this->payload = payload;}
    std::shared_ptr<CommunicationProtocol> get_payload() override {return this->payload;}
	void recalculate_fields() override {}

	std::shared_ptr<EthernetFrameInterface> copy() {return std::make_shared<EthernetFrame>(*this);}
};



#endif /* ETHERNETFRAME_H_ */
