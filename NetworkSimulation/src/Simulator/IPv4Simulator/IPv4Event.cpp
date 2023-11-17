#include "IPv4Event.h"
#include "IPv4EventRule.h"

void IPv4Event::apply_rules(std::shared_ptr<BaseScheduler> scheduler) {
    for (auto rule : event_rules) {
        rule->handle(IPv4EventPtr(shared_from_this()), scheduler);
    }
}