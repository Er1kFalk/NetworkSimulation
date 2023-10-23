/*
 * TrafficClassInterface.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include <array>

#ifndef TRAFFICCLASSINTERFACE_H_
#define TRAFFICCLASSINTERFACE_H_

class TrafficClassInterface {
public:
    virtual void set_ds(unsigned char ds) = 0;
    virtual void set_ecn(unsigned char ecn) = 0;
    virtual unsigned char get_ds() = 0;
    virtual unsigned char get_ecn() = 0;
    virtual std::array<unsigned char, 1> get_traffic_class_as_array() = 0;
    virtual unsigned char get_traffic_class_as_char() = 0;
};

#endif /* TRAFFICCLASSINTERFACE_H_ */
