
#ifndef EVENT_H_
#define EVENT_H_

#include <memory>
#include "../../ConfigReader/GeneratorFileStruct.h"
#include "EventTypeDefs.h"

class BaseScheduler;

class Event {
private:
    uint32_t id;
    Transmitter tx;
public:
    virtual void apply_rules(std::shared_ptr<BaseScheduler> scheduler) = 0;
    void set_transmitter(Transmitter tx) {this->tx = tx;}
    Transmitter get_transmitter() {return this->tx;}
    void set_id(uint32_t id) {this->id = id;}
    uint32_t get_id() {return this->id;}
};

#endif