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

class CommunicationProtocol {
private:
	std::vector<unsigned char> payload;
	std::vector<unsigned char> header;
public:
	virtual ~CommunicationProtocol() = default;

	virtual std::vector<unsigned char> get_header() = 0;
	virtual std::vector<unsigned char> get_header_payload() = 0;
	virtual	void set_payload(std::vector<unsigned char> payload) {
		this->payload = payload;
	}
	std::vector<unsigned char> get_payload () {
		return payload;
	}
};

class LLC_PDU : public CommunicationProtocol {
private:
	std::vector<unsigned char> destination_address;
	std::vector<unsigned char> source_address;
public:
	virtual ~LLC_PDU() = default;

	virtual void set_destination_address(std::vector<unsigned char> destination) {
		this->destination_address = destination;
	}
	virtual void set_source_address(std::vector<unsigned char> source) {
		this->source_address = source;
	}

	std::vector<unsigned char> get_destination_address() {
		return destination_address;
	}
	std::vector<unsigned char> get_source_address() {
		return source_address;
	}
};

class X {
public:
	void test(){}
};

class EthernetFrame : public LLC_PDU {
	static inline const uint8_t DESTINATION_ADDRESS_SIZE = 6;
	static inline const uint8_t SOURCE_ADDRESS_SIZE = 6;
	static inline const uint8_t ETHERTYPE_SIZE = 2;

	std::vector<unsigned char> ethertype;
	static inline const std::map<std::string, std::vector<unsigned char>> ethertype_common_values = {
		{"ipv4", {0x08, 0x00}},
		{"arp", {0x08, 0x06}},
		{"ipv6", {0x86, 0xDD}}
	};

public:
	EthernetFrame () {}

	virtual ~EthernetFrame() {}

	void set_destination_address(std::vector<unsigned char> destination_address) override;

	void set_source_address(std::vector<unsigned char> source_address) override;

	void set_ethertype(std::vector<unsigned char> ethertype) {
		this->ethertype = ethertype;
	}

	void set_ethertype(std::string ethertype);

	std::vector<unsigned char> getEthertype() {
		return ethertype;
	}

	std::vector<unsigned char> get_header() override;

	std::vector<unsigned char> get_header_payload() override;

};



#endif /* ETHERNETHEADER_H_ */
