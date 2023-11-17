#include <memory>

#ifndef TCPSIMULATORTYPEDEFS_H_
#define TCPSIMULATORTYPEDEFS_H_

class TCPEventRule;
class TCPEvent;
class TCPScheduler;

typedef std::shared_ptr<TCPEventRule> TCPEventRulePtr;
typedef std::shared_ptr<TCPEvent> TCPEventPtr;
typedef std::shared_ptr<TCPScheduler> TCPSchedulerPtr;
enum class Transmitter {Client, Server};

#endif