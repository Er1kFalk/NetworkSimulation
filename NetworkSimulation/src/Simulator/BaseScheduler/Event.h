
#ifndef EVENT_H_
#define EVENT_H_

#include <memory>

class BaseScheduler;

class Event {
public:
    virtual void apply_rules(std::shared_ptr<BaseScheduler> scheduler) = 0;
};

#endif