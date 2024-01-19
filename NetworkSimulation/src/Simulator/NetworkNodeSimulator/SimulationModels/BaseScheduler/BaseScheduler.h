//#include "../NetworkNodeSimulator/NetworkNodeSimulator.h"
#ifndef BASESCHEDULER_H_
#define BASESCHEDULER_H_

#include <memory>
#include<queue>
#include <tuple>
#include "../../../CustomOperators/TupleGreaterThan.h"


class NetworkNodeSimulator;
class Event;

class BaseScheduler : public std::enable_shared_from_this<BaseScheduler> {
private:    
    std::shared_ptr<NetworkNodeSimulator> parent;
    uint32_t scheduler_time_sec;
    uint32_t scheduler_time_us;
    typedef std::tuple<std::shared_ptr<Event>, uint32_t, uint32_t> EventQueueElement;
    std::priority_queue<EventQueueElement, std::vector<EventQueueElement>, TupleGreaterThan<std::shared_ptr<Event>>> events;

public:
    BaseScheduler() {
        this->parent = nullptr;
        this->scheduler_time_sec = 0;
        this->scheduler_time_us = 0;
    }
    void set_parent(std::shared_ptr<NetworkNodeSimulator> parent) {this->parent = parent;}
    std::shared_ptr<NetworkNodeSimulator> get_parent() {return parent;}

    void set_scheduler_time_sec(uint32_t scheduler_time_sec) {
        this->scheduler_time_sec = scheduler_time_sec;
    }
    uint32_t get_scheduler_time_sec() {return this->scheduler_time_sec;}
    void set_scheduler_time_us(uint32_t scheduler_time_us) {
        this->scheduler_time_us = scheduler_time_us;
    }
    uint32_t get_scheduler_time_us() {return this->scheduler_time_us;}


    void dispatch_next_event();

    void schedule(std::shared_ptr<Event> e, uint32_t time_s, uint32_t time_us);
    
    bool contains_events();
};


#endif