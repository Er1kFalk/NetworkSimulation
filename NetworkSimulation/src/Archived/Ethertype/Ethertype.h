/*
 * Ethertype.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "EthertypeInterface.h"
#include "ArrayUtils/ArrayUtils.h"
#include <map>
#include <utility>

#ifndef ETHERTYPE_H_
#define ETHERTYPE_H_

class Ethertype : public EthertypeInterface {
private:
	std::array<unsigned char, 2> ethertype;
	// static const std::vector<std::pair<ProtocolConstants::EthertypeName, std::array<unsigned char, 2>>> ethertype_common_values;
public:
	Ethertype(std::array<unsigned char, 2> ethertype) {
		this->ethertype = ethertype;
	}

	void set_ethertype(std::array<unsigned char, 2> ethertype) override {this->ethertype = ethertype;}

	// void set_ethertype(ProtocolConstants::EthertypeName ethertype) override;

	std::array<unsigned char, 2> get_ethertype() override {
		return ethertype;
	}
};


#endif /* ETHERTYPE_H_ */
