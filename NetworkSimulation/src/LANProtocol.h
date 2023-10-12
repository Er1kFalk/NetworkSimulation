/*
 * LANProtocol.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "MACAddress/MACAddressInterface.h"

#ifndef LANPROTOCOL_H_
#define LANPROTOCOL_H_

class LANProtocol : public CommunicationProtocol {
protected:
	MACAddressInterface *destination_address;
	MACAddressInterface *source_address;
public:
	virtual ~LANProtocol() = default;

	virtual void set_destination_address(MACAddressInterface *destination_address) = 0;
	virtual void set_source_address(MACAddressInterface *source_address) = 0;

	virtual MACAddressInterface* get_destination_address() = 0;
	virtual MACAddressInterface* get_source_address() = 0;
};

#endif /* LANPROTOCOL_H_ */
