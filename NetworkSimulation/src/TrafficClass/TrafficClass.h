/*
 * TrafficClass.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include <vector>
#include "TrafficClassInterface.h"

#ifndef TRAFFICCLASS_H_
#define TRAFFICCLASS_H_

class TrafficClass : public TrafficClassInterface {
private:
    unsigned char traffic_class;
public:
    TrafficClass() {
        this->traffic_class = 0;
    }
    void set_ds(unsigned char ds) override;
    void set_ecn(unsigned char ecn) override;
    unsigned char get_ds_ecn() override {
        return traffic_class;
    }
};

#endif /* TRAFFICCLASSINTERFACE_H_ */