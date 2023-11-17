// #include "TCPScheduler.h"
// #include "TCPEvent.h"
// #include "TCPEventRules.h"
// #include "../MainSimulator/MainSimulator.h"

// std::map<std::tuple<NetworkLayer, Transmitter>, TCPEventRulePtr> TCPScheduler::pass_to_layer = {
//     {{NetworkLayer::IPv4, Transmitter::Client}, TCPEventRulePtr(new PassClientStateToIPv4)},
//     {{NetworkLayer::IPv4, Transmitter::Server}, TCPEventRulePtr(new PassServerStateToIPv4)}
// };

// void TCPScheduler::schedule(TCPEventPtr e, std::vector<TCPEventRulePtr> r, uint64_t time) {
//     if (time < get_scheduler_time()) {
//         set_scheduler_time(time);
//     }
    
//     e->set_event_rules(r);
//     this->events.push({e, time});
// }

// void TCPScheduler::dispatch(TCPEventPtr e, uint64_t time) {
//     // apply rules to event
//     for (auto rule : e->get_event_rules()) {
//         rule->handle(e, TCPSchedulerPtr(this), np);
//     }
// }

// void TCPScheduler::dispatch_next_event() {
//     EventQueueElement e = events.top();
//     TCPEventPtr event = std::get<TCPEventPtr>(e);
//     for (auto rule : event->get_event_rules()) {
//         rule->handle(event, TCPSchedulerPtr(this), np);
//     }
//     pass_to_layer[{event->get_nlayer(), event->get_tx()}]->handle(event, TCPSchedulerPtr(this), np); // pass event to correct network layer
//     events.pop();
//     set_scheduler_time(std::get<uint64_t>(events.top())); // update scheduler time
// }

// bool TCPScheduler::contains_events() {
//     return !events.empty();
// }