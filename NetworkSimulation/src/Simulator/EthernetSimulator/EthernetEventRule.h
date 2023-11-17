#ifndef ETHERNETEVENTRULE_H_
#define ETHERNETEVENTRULE_H_

#include "EthernetSimulatorTypeDefs.h"
#include "EthernetEvent.h"
#include "EthernetSimulatorTypeDefs.h"

class BaseScheduler;

class EthernetEventRule {

public:
    virtual void handle(EthernetEventPtr e, std::shared_ptr<BaseScheduler> scheduler) = 0;
};

class SendEthernetData : public EthernetEventRule {

public:
    void handle(EthernetEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

#endif