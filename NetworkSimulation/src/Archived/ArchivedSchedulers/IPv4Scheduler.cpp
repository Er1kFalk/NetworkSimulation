// #include "IPv4Scheduler.h"
// #include "IPv4Event.h"
// #include "IPv4EventRule.h"

// void IPv4Scheduler::schedule(std::shared_ptr<IPv4Event> e, std::vector<std::shared_ptr<IPv4EventRule>> r, uint64_t time) {
//     if (time < get_scheduler_time()) {
//         set_scheduler_time(time);
//     }

//     e->set_event_rules(r);
//     events.push({e, time});
// }

// void IPv4Scheduler::dispatch(std::shared_ptr<IPv4Event> e, uint64_t time) {
//     for (auto rule : e->get_event_rules()) {
//         rule->handle(e, std::shared_ptr<IPv4Scheduler>(this));
//     }
// }
