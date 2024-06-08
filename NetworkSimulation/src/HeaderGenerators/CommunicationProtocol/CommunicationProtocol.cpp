#include "CommunicationProtocol.h"

bool CommunicationProtocol::equal(std::shared_ptr<CommunicationProtocol> c) {
    std::vector<unsigned char> thisProtocol = this->header_payload_to_array();
    std::vector<unsigned char> cProtocol = c->header_payload_to_array();
    return thisProtocol == cProtocol;
}
