#include "TrafficClass.h"
#include <stdexcept>

void TrafficClass::set_ds(unsigned char ds) {
    if (ds & 0b11000000 != 0) { // if there is non-zero value at 2 highest bits
        throw std::invalid_argument("DS must only occupy bits 0-5");
    }

    this->traffic_class = this->traffic_class | ds;
}

void TrafficClass::set_ecn(unsigned char ecn) {
    if (ecn & 0b00111111 != 0) { // if there is non-zero value at 6 lowest bits
        throw std::invalid_argument("ECN must only occupy bits 6-7");
    }

    this->traffic_class = this->traffic_class | ecn;
}