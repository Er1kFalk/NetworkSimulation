#ifndef IPV4SIMULATORTYPEDEFS_H_
#define IPV4SIMULATORTYPEDEFS_H_

#include <memory>

class IPv4EventRule;
class IPv4Event;
class IPv4Scheduler;

typedef std::shared_ptr<IPv4EventRule> IPv4EventRulePtr;
typedef std::shared_ptr<IPv4Event> IPv4EventPtr;
typedef std::shared_ptr<IPv4Scheduler> IPv4SchedulerPtr;

#endif