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
	std::vector<unsigned char> ethertype;
	static const std::vector<std::pair<std::string, std::vector<unsigned char>>> ethertype_common_values;
public:
	void set_ethertype(std::vector<unsigned char> ethertype) override;

	void set_ethertype(std::string ethertype) override;

	std::vector<unsigned char> get_ethertype() override {
		return ethertype;
	}

	const int get_octet_length() {
		return 2;
	}
};


#endif /* ETHERTYPE_H_ */
