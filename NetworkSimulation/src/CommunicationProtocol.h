/*
 * CommunicationProtocol.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <vector>
#include <memory>

#ifndef COMMUNICATIONPROTOCOL_H_
#define COMMUNICATIONPROTOCOL_H_

class CommunicationProtocol {
private:
	std::shared_ptr<CommunicationProtocol> payload;
public:
	virtual ~CommunicationProtocol() = default;

	virtual std::vector<unsigned char> to_array() = 0;
	void set_payload(std::shared_ptr<CommunicationProtocol> payload) {
		this->payload = payload;
	}
	std::shared_ptr<CommunicationProtocol> get_payload () {
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

	Data(std::vector<unsigned char> data) {
		set_data(data);
	}

	Data(std::vector<unsigned char> data, std::shared_ptr<CommunicationProtocol> payload) {
		set_data(data);
		set_payload(payload);
	}
};


#endif /* COMMUNICATIONPROTOCOL_H_ */
