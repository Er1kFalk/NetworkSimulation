#include "../CommunicationProtocol/CommunicationProtocol.h"

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
