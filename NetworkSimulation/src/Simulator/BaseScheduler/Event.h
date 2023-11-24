
#ifndef EVENT_H_
#define EVENT_H_

#include <memory>
#include "../../ConfigReader/GeneratorFileStruct.h"
#include "EventTypeDefs.h"
#include <iostream>

class BaseScheduler;

class Event {
private:
    uint32_t id;
    std::shared_ptr<GFStructs::TransmittingNow> tx;
public:
    virtual void apply_rules(std::shared_ptr<BaseScheduler> scheduler) = 0;
    void set_transmitter(GFStructs::TransmittingNow tx) {
        this->tx = std::make_shared<GFStructs::TransmittingNow>(tx);
    }
    GFStructs::TransmittingNow get_transmitter() {return *(this->tx);}
    void set_id(uint32_t id) {this->id = id;}
    uint32_t get_id() {return this->id;}
};

#endif