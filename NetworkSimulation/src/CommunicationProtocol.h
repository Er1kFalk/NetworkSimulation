/*
 * CommunicationProtocol.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <vector>

#ifndef COMMUNICATIONPROTOCOL_H_
#define COMMUNICATIONPROTOCOL_H_

class CommunicationProtocol {
private:
	CommunicationProtocol *payload;
public:
	virtual ~CommunicationProtocol() = default;

	virtual std::vector<unsigned char> to_array() = 0;
	void set_payload(CommunicationProtocol *payload) {
		this->payload = payload;
	}
	CommunicationProtocol* get_payload () {
		return payload;
	}
};

class Data : public CommunicationProtocol {
private:
	std::vector<unsigned char> data;
public:
	std::vector<unsigned char> to_array() override {
		return data;
	}
	void set_data(std::vector<unsigned char> data) {
		this->data = data;
	}
};


#endif /* COMMUNICATIONPROTOCOL_H_ */
