#include "EthernetEvent.h"


void EthernetEvent::apply_rules(std::shared_ptr<BaseScheduler> scheduler) {
    for (auto rule : event_rules) {
        rule->handle(EthernetEventPtr(shared_from_this()), scheduler);
    }
}