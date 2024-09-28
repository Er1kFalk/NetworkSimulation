
#ifndef EVENT_H_
#define EVENT_H_

#include <memory>
#include "../../../../ConfigReader/GeneratorFileConfigReader/GeneratorFileStruct.h"
#include "EventTypeDefs.h"

class BaseScheduler;
class NetworkNodeSimulator;

class Event {
private:
    uint32_t id;
    std::shared_ptr<GFStructs::TransmittingNow> tx;
    std::shared_ptr<NetworkNodeSimulator> parent;
public:
    virtual void apply_rules(std::shared_ptr<BaseScheduler> scheduler) = 0;
    void set_transmitter(GFStructs::TransmittingNow tx) {
        this->tx = std::make_shared<GFStructs::TransmittingNow>(tx);
    }
    GFStructs::TransmittingNow get_transmitter() {return *(this->tx);}
    void set_id(uint32_t id) {this->id = id;}
    uint32_t get_id() {return this->id;}
    void set_parent(std::shared_ptr<NetworkNodeSimulator> parent) {this->parent = parent;}
    std::shared_ptr<NetworkNodeSimulator> get_parent() {return parent;}
};

#endif
