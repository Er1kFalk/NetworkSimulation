/*
 * ProtocolType.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include "ProtocolTypeInterface.h"

#ifndef PROTOCOLTYPE_H_
#define PROTOCOLTYPE_H_

class ProtocolType : public ProtocolTypeInterface {
private:
    unsigned char protocol;
public:
    void set_protocol(unsigned char protocol) override {this->protocol = protocol;}
    std::array<unsigned char, 1> get_protocol_as_array() override {return {protocol};}
    unsigned char get_protocol_as_char() override {return protocol;}

    ProtocolType(unsigned char protocol) {
        set_protocol(protocol);
    }
};


#endif /* PROTOCOLTYPE_H_ */
