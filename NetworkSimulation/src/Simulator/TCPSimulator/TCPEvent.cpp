#include "TCPEvent.h"
#include "TCPEventRules.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../MainSimulator/MainSimulator.h"
#include <iostream>

void TCPEvent::apply_rules(std::shared_ptr<BaseScheduler> scheduler) {
    for (auto rule : event_rules) {
        rule->handle(shared_from_this(), scheduler);
    }
    
}