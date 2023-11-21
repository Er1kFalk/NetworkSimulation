#include "EthernetEvent.h"


void EthernetEvent::apply_rules(std::shared_ptr<BaseScheduler> scheduler) {
    for (auto rule : event_rules) {
        rule->handle(EthernetEventPtr(shared_from_this()), scheduler);
    }
}

std::shared_ptr<EthernetEvent> EthernetEvent::copy() {
    auto e = std::make_shared<EthernetEvent>(*this);
    e->set_event_rules({});
    e->set_ethernet_frame(this->ethernet_frame->copy());

    return e;
}