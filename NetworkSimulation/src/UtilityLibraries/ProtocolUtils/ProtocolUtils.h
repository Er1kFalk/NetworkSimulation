#ifndef PROTOCOLUTILS_H_
#define PROTOCOLUTILS_H_

#include <vector>
#include <cassert>
#include "../../HeaderGenerators/CommunicationProtocol/CommunicationProtocol.h"
#include <memory>

namespace ProtocolUtils {
    
    unsigned short int calculate_internet_checksum(std::vector<unsigned char> data);
    bool verify_internet_checksum(std::vector<unsigned char> data, unsigned short int checksum);



    std::shared_ptr<CommunicationProtocol> build_protocol_stack_from_vector(std::vector<std::shared_ptr<CommunicationProtocol>> v);
}

#endif