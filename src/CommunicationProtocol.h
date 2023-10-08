/*
 * CommunicationProtocol.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#ifndef COMMUNICATIONPROTOCOL_H_
#define COMMUNICATIONPROTOCOL_H_

class CommunicationProtocol {
private:
	std::vector<unsigned char> payload;
public:
	virtual ~CommunicationProtocol() = default;

	virtual std::vector<std::vector<unsigned char>> to_array() = 0;
	virtual	void set_payload(std::vector<unsigned char> payload) {
		this->payload = payload;
	}
	std::vector<unsigned char> get_payload () {
		return payload;
	}
};



#endif /* COMMUNICATIONPROTOCOL_H_ */
