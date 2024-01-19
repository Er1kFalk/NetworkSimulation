#ifndef IPV4EVENT_H_
#define IPV4EVENT_H_

#include <vector>
#include <memory>
#include <map>
#include "../../../../HeaderGenerators/IPv4Packet/IPv4PacketInterface.h"
#include "../../../../HeaderGenerators/CommunicationProtocol/CommunicationProtocol.h"
#include "IPv4SimulatorTypeDefs.h"
#include "../../SimulatorTypeDefs.h"
#include "../BaseScheduler/Event.h"


class IPv4EventRule;

class IPv4Event : public Event, public std::enable_shared_from_this<IPv4Event> {
protected: 
    std::vector<IPv4EventRulePtr> event_rules;
    std::shared_ptr<IPv4PacketInterface> ipv4_packet;
    LinkLayer llayer;
    static std::map<LinkLayer, IPv4EventRulePtr> pass_to_layer;
public:
    void set_ipv4_packet(std::shared_ptr<IPv4PacketInterface> ipv4_packet) {
        this->ipv4_packet = ipv4_packet;
        set_transmitter(GFStructs::TransmittingNow::Client);
    }
    std::shared_ptr<IPv4PacketInterface> get_ipv4_packet() {return ipv4_packet;}
    void set_event_rules(std::vector<IPv4EventRulePtr> event_rules)  {this->event_rules = event_rules;}
    std::vector<IPv4EventRulePtr> get_event_rules() {return this->event_rules;}
    void set_llayer(LinkLayer llayer) {this->llayer = llayer;}
    LinkLayer get_llayer() {return this->llayer;}
    void apply_rules(std::shared_ptr<BaseScheduler> scheduler) override;
    std::shared_ptr<IPv4Event> copy();
};

#endif