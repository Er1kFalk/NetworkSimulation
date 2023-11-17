//#include "../MainSimulator/MainSimulator.h"
#ifndef BASESCHEDULER_H_
#define BASESCHEDULER_H_

#include <memory>
#include<queue>
#include <tuple>
#include "../CustomOperators/TupleGreaterThan.h"


class MainSimulator;
class Event;

class BaseScheduler : public std::enable_shared_from_this<BaseScheduler> {
private:    
    std::shared_ptr<MainSimulator> parent;
    uint64_t scheduler_time;
    typedef std::tuple<std::shared_ptr<Event>, uint64_t> EventQueueElement;
    std::priority_queue<EventQueueElement, std::vector<EventQueueElement>, TupleGreaterThan<std::shared_ptr<Event>>> events;

public:
    BaseScheduler() {
        this->parent = nullptr;
        this->scheduler_time = 0;
    }
    void set_parent(std::shared_ptr<MainSimulator> parent) {this->parent = parent;}
    std::shared_ptr<MainSimulator> get_parent() {return parent;}

    void set_scheduler_time(uint64_t scheduler_time) {this->scheduler_time = scheduler_time;}
    uint64_t get_scheduler_time() {return this->scheduler_time;}
    void dispatch_next_event();

    void schedule(std::shared_ptr<Event> e, uint64_t time);
    
    bool contains_events();
};


#endif