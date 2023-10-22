/*
 * TrafficClassInterface.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include <vector>

#ifndef TRAFFICCLASSINTERFACE_H_
#define TRAFFICCLASSINTERFACE_H_

class TrafficClassInterface {
public:
    virtual void set_ds(unsigned char ds) = 0;
    virtual void set_ecn(unsigned char ecn) = 0;
    virtual unsigned char get_ds_ecn() = 0;
};

#endif /* TRAFFICCLASSINTERFACE_H_ */
