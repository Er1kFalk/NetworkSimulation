/*
 * TrafficClass.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include <array>
#include "TrafficClassInterface.h"

#ifndef TRAFFICCLASS_H_
#define TRAFFICCLASS_H_

class TrafficClass : public TrafficClassInterface {
private:
    unsigned char traffic_class;
public:
    
    void set_ds(unsigned char ds) override;
    void set_ecn(unsigned char ecn) override;
    unsigned char get_ds() override {return traffic_class >> 2;}
    unsigned char get_ecn() override {return (0b11 & traffic_class);}
    std::array<unsigned char, 1> get_traffic_class_as_array() override {return {traffic_class};}
    unsigned char get_traffic_class_as_char() override {return traffic_class;}

    TrafficClass(unsigned char ds, unsigned char ecn) {
        set_ds(ds);
        set_ecn(ecn);
    }
};

#endif /* TRAFFICCLASSINTERFACE_H_ */