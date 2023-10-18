/*
 * EthertypeInterface.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <string>
#include <array>
#include <vector>

#ifndef ETHERTYPEINTERFACE_H_
#define ETHERTYPEINTERFACE_H_

class EthertypeInterface {
public:
	virtual ~EthertypeInterface() = default;
	virtual void set_ethertype(std::vector<unsigned char> ethertype) = 0;
	virtual void set_ethertype(std::string ethertype) = 0;
	virtual std::vector<unsigned char> get_ethertype() = 0;
	virtual const int get_octet_length() = 0;
};

#endif /* ETHERTYPEINTERFACE_H_ */
