/*
 * LANProtocol.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include "MACAdress/MACAdressInterface.h"

#ifndef LANPROTOCOL_H_
#define LANPROTOCOL_H_

class LANProtocol : public CommunicationProtocol {
protected:
	MACAdressInterface *destination_address;
	MACAdressInterface *source_address;
public:
	virtual ~LANProtocol() = default;

	virtual void set_destination_address(MACAdressInterface *destination_address) = 0;
	virtual void set_source_address(MACAdressInterface *source_address) = 0;

	virtual MACAdressInterface* get_destination_address() = 0;
	virtual MACAdressInterface* get_source_address() = 0;
};

#endif /* LANPROTOCOL_H_ */
