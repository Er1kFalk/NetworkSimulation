// #include <vector>
// #include <tuple>
// #include <memory>
// #include <queue>
// #include <map>

// #include "../NetworkProperties.h"
// #include "../BaseScheduler/BaseScheduler.h"
// #include "TCPSimulatorTypeDefs.h"
// #include "../CustomOperators/TupleGreaterThan.h"
// #include "../MainSimulator/MainSimulator.h"
// #include "../MainSimulator/SimulatorTypeDefs.h"

// #ifndef TCPSCHEDULER_H_
// #define TCPSCHEDULER_H_

// class TCPEvent;
// class TCPEventRule;



// class TCPScheduler : public BaseScheduler {
// private:
//     typedef std::tuple<TCPEventPtr, uint64_t> EventQueueElement;
    
//     std::priority_queue<EventQueueElement, std::vector<EventQueueElement>, TupleGreaterThan<TCPEventPtr>> events;

//     std::shared_ptr<NetworkProperties> np;

    
//     static std::map<std::tuple<NetworkLayer, Transmitter>, TCPEventRulePtr> pass_to_layer;
// public:
//     TCPScheduler(std::shared_ptr<NetworkProperties> np, std::shared_ptr<MainSimulator> parent) {
//         this->np = np;
//         this->set_parent(parent);
//     }
//     void schedule(TCPEventPtr e, std::vector<TCPEventRulePtr> r, uint64_t time);
//     void dispatch(TCPEventPtr e, uint64_t time);
//     void dispatch_next_event() override;
    
//     bool contains_events() override;
// };

// #endif