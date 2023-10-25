#include "TrafficClass.h"
#include <stdexcept>

void TrafficClass::set_ds(unsigned char ds) {
    if (ds > 63) { // ds should be between 0 and 63
        throw std::invalid_argument("DS must be in range [0-63]");
    }

    // set 6 upper bits to ds
    this->traffic_class |= (ds << 2);
}

void TrafficClass::set_ecn(unsigned char ecn) {
    if (ecn > 3) { // ECN can be 0b00 (0), 0b01 (1), 0b10 (2), 0b11 (3)
        throw std::invalid_argument("ECN must be in range 0-3");
    }

    // set 2 lower bits to ecn
    this->traffic_class |= ecn;
}