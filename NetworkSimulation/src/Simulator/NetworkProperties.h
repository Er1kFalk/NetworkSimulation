#include "../RandomUtils/RandomUtils.h"
#include <memory>
#include "MainSimulator/SimulatorTypeDefs.h"

#ifndef NETWORKPROPERTIES_H_
#define NETWORKPROPERTIES_H_

struct RTT {
    double mean;
    double stddev;
};

class NetworkProperties {
private:
    std::shared_ptr<RandomUtils> generator;
    double packet_drop_prop;
    RTT rtt;
    NetworkLayer nlayer;
public:
    NetworkProperties(RTT rtt, NetworkLayer nlayer) {
        this->generator = std::shared_ptr<RandomUtils>(new RandomUtils());
        this->rtt = rtt;
        this->nlayer = nlayer;
    }

    double get_rtt() {
        return generator->generate_normal_number(rtt.mean, rtt.stddev);
    }
    void set_packet_drop_prop(double p) {this->packet_drop_prop = p;}
    double get_packet_drop_prop() {return this->packet_drop_prop;}
    bool is_packet_dropped() {return generator->generate_uniform_number() <= this->packet_drop_prop;}
    NetworkLayer get_nlayer() {return this->nlayer;}
};

#endif