#include "BaseScheduler.h"
#include "Event.h"
#include <exception>


void BaseScheduler::dispatch_next_event() {
    auto eq = events.top();

    std::shared_ptr<Event> event = std::get<std::shared_ptr<Event>>(eq);
    this->scheduler_time_sec = std::get<1>(eq);
    this->scheduler_time_us = std::get<2>(eq);
    
    auto schedulerPtr = shared_from_this();

    event->apply_rules(shared_from_this());
    events.pop();
}

void BaseScheduler::schedule(std::shared_ptr<Event> e, uint32_t time_s, uint32_t time_us) {
    while (time_us > 1000000 && time_us % 1000000 == 0) { // then it is a multiple of a second
        time_s++;
        time_us-=1000000;
    }
    

    EventQueueElement x = EventQueueElement(e, this->scheduler_time_sec+time_s, this->scheduler_time_us + time_us);
    this->events.push(x);
}

bool BaseScheduler::contains_events() {
    return !events.empty();
}
