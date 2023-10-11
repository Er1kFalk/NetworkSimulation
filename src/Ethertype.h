/*
 * Ethertype.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "EthertypeInterface.h"
#include "ArrayUtils/ArrayUtils.h"
#include <map>

#ifndef ETHERTYPE_H_
#define ETHERTYPE_H_

class Ethertype : public EthertypeInterface {
private:
	std::vector<unsigned char> ethertype;
	static const std::map<std::string, std::vector<unsigned char>> ethertype_common_values;
public:
	void set_ethertype(std::array<unsigned char, 2> ethertype) override {
		this->ethertype = ArrayUtils::to_vector(ethertype);
	}

	void set_ethertype(std::string ethertype) override;

	std::vector<unsigned char> get_ethertype() {
		return ethertype;
	}

	std::string to_string() override;
};


#endif /* ETHERTYPE_H_ */
