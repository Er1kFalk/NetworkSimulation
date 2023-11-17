#ifndef ETHERNETSIMULATORTYPEDEFS_H_
#define ETHERNETSIMULATORTYPEDEFS_H_

#include <memory>

class EthernetEvent;
class EthernetEventRule;
class EthernetScheduler;

typedef std::shared_ptr<EthernetEventRule> EthernetEventRulePtr;
typedef std::shared_ptr<EthernetEvent> EthernetEventPtr;
typedef std::shared_ptr<EthernetScheduler> EthernetSchedulerPtr;

#endif