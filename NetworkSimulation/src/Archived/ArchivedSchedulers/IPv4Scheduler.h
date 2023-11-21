// #include <memory>
// #include <tuple>
// #include <vector>
// #include <queue>
// #include <limits>

// #include "../BaseScheduler/BaseScheduler.h"
// #include "IPv4SimulatorTypeDefs.h"
// #include "../CustomOperators/TupleGreaterThan.h"

// #ifndef IPV4SCHEDULER_H_
// #define IPV4SCHEDULER_H_

// class IPv4Scheduler : public BaseScheduler {
// private:
    
//     typedef std::tuple<IPv4EventPtr, uint64_t> EventQueueElement;
    
//     std::priority_queue<EventQueueElement, std::vector<EventQueueElement>, TupleGreaterThan<IPv4EventPtr>> events;

// public:
//     IPv4Scheduler(std::shared_ptr<NetworkNodeSimulator> parent) {
//         this->set_parent(parent);
//         set_scheduler_time(std::numeric_limits<uint64_t>::max());
//     }
//     void schedule(IPv4EventPtr e, std::vector<IPv4EventRulePtr> r, uint64_t time);
//     void dispatch(IPv4EventPtr e, uint64_t time);

//     void dispatch_next_event() override {
        
//     }

//     bool contains_events() {
//         if (events.empty()) {
//             return false;
//         } else {
//             return true;
//         }
//     }
// };



// #endif