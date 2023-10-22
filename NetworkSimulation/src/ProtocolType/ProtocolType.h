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
    void set_protocol(unsigned char protocol) override {
        this->protocol = protocol;
    }
    unsigned char get_protocol() {
        return protocol;
    }
};


#endif /* PROTOCOLTYPE_H_ */
