/*
 * ProtocolTypeInterface.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include <array>

#ifndef PROTOCOLTYPEINTERFACE_H_
#define PROTOCOLTYPEINTERFACE_H_

class ProtocolTypeInterface {
public:
    virtual void set_protocol(unsigned char protocol) = 0;
    virtual std::array<unsigned char, 1> get_protocol_as_array() = 0;
    virtual unsigned char get_protocol_as_char() = 0;
};


#endif /* PROTOCOLTYPEINTERFACE_H_ */
