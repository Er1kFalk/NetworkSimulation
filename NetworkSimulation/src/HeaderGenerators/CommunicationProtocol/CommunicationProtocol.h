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

#endif /* COMMUNICATIONPROTOCOL_H_ */
