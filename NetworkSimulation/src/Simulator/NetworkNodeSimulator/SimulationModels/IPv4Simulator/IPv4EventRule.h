#ifndef IPV4EVENTRULE_H_
#define IPV4EVENTRULE_H_

#include "IPv4SimulatorTypeDefs.h"

class IPv4Event;
class BaseScheduler;

class IPv4EventRule {

public:
    virtual void handle(IPv4EventPtr e) = 0;
};

class SendIPv4DataClient : public IPv4EventRule {
public:
    void handle(IPv4EventPtr e) override;
};

class ReceiveIPv4Data : public IPv4EventRule {
public:
    void handle(IPv4EventPtr e) override;
};

class PassIPv4DataToEthernet : public IPv4EventRule {
public:
    void handle(IPv4EventPtr e) override;
};

#endif
