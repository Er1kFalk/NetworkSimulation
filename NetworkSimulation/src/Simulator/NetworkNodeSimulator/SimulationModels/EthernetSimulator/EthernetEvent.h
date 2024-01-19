#ifndef ETHERNETEVENT_H_
#define ETHERNETEVENT_H_

#include "EthernetSimulatorTypeDefs.h"
#include "../../../../HeaderGenerators/EthernetFrame/EthernetFrameInterface.h"
#include "../BaseScheduler/Event.h"
#include "EthernetEventRule.h"


class EthernetEvent : public Event, public std::enable_shared_from_this<EthernetEvent> {
protected: 
    std::vector<EthernetEventRulePtr> event_rules;
    std::shared_ptr<EthernetFrameInterface> ethernet_frame;
public:
    void set_ethernet_frame(std::shared_ptr<EthernetFrameInterface> ethernet_frame) {
        this->ethernet_frame= ethernet_frame;
    }
    std::shared_ptr<EthernetFrameInterface> get_ethernet_frame() {return ethernet_frame;}
    void set_event_rules(std::vector<EthernetEventRulePtr> event_rules)  {this->event_rules = event_rules;}
    std::vector<EthernetEventRulePtr> get_event_rules() {return this->event_rules;}
    void apply_rules(std::shared_ptr<BaseScheduler> scheduler) override;
    std::shared_ptr<EthernetEvent> copy();
};

#endif