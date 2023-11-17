#include "BaseScheduler.h"
#include "Event.h"
#include <iostream>

void BaseScheduler::dispatch_next_event() {
    std::shared_ptr<Event> e = std::get<std::shared_ptr<Event>>(events.top());

    e->apply_rules(shared_from_this());
    events.pop();
}

void BaseScheduler::schedule(std::shared_ptr<Event> e, uint64_t time) {
    if (time < get_scheduler_time()) {
        set_scheduler_time(time);
    }
    this->events.push({e, time});
}

bool BaseScheduler::contains_events() {
    return !events.empty();
}