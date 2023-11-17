

#include <vector>
#include <memory>

#ifndef COMMUNICATIONPROTOCOL_H_
#define COMMUNICATIONPROTOCOL_H_

class CommunicationProtocol {
public:
	virtual ~CommunicationProtocol() = default;

	virtual std::vector<unsigned char> header_to_array() = 0;
	virtual std::vector<unsigned char> header_payload_to_array() = 0;
	virtual void set_payload(std::shared_ptr<CommunicationProtocol> payload) = 0;
	virtual std::shared_ptr<CommunicationProtocol> get_payload () = 0;
	virtual void recalculate_fields() = 0;
};

class Data : public CommunicationProtocol {
private:
	std::vector<unsigned char> data;
	std::shared_ptr<CommunicationProtocol> payload;
public:
	std::vector<unsigned char> header_to_array() override {
		return data;
	}

	virtual std::vector<unsigned char> header_payload_to_array() override {
		return data;
	}

	void set_data(std::vector<unsigned char> data) {
		this->data = data;
	}

	Data(std::vector<unsigned char> data) {
		this->data = data;
	}

	void set_payload(std::shared_ptr<CommunicationProtocol> payload) override {this->payload = payload;}
	std::shared_ptr<CommunicationProtocol> get_payload () override {return this->payload;}
	void recalculate_fields() override {}
};


#endif /* COMMUNICATIONPROTOCOL_H_ */
