#ifndef ETHERNETEVENTRULE_H_
#define ETHERNETEVENTRULE_H_

#include "EthernetSimulatorTypeDefs.h"
#include "EthernetEvent.h"
#include "EthernetSimulatorTypeDefs.h"

class BaseScheduler;

class EthernetEventRule {

public:
    virtual void handle(EthernetEventPtr e) = 0;
};

class SendEthernetData : public EthernetEventRule {

public:
    void handle(EthernetEventPtr e) override;
};

#endif
