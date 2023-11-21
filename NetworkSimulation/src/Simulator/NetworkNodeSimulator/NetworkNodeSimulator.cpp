#include "NetworkNodeSimulator.h"
#include "../NetworkProperties.h"
#include "../../CommunicationProtocol.h"
#include "../IPv4Simulator/IPv4Event.h"
#include "../../IPv4Packet/IPv4Packet.h"
#include "../IPv4Simulator/IPv4EventRule.h"
#include "../TCPSimulator/TCPEvent.h"
#include "../TCPSimulator/TCPEventRules.h"
#include "../../EthernetFrame/EthernetFrameInterface.h"
#include "../EthernetSimulator/EthernetEvent.h"
#include "../EthernetSimulator/EthernetEventRule.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../../RandomUtils/RandomUtils.h"
#include "../../PCAPWriter/PCAPWriter.h"
#include <pcap/pcap.h>
#include <iostream>

void NetworkNodeSimulator::initialize() {
    scheduler = std::shared_ptr<BaseScheduler>(new BaseScheduler());
    scheduler->set_parent(shared_from_this());
}

void NetworkNodeSimulator::run() {
    while(scheduler->contains_events()) {
        scheduler->dispatch_next_event();
    }
}

NetworkNodeSimulator::NetworkNodeSimulator(std::shared_ptr<NetworkProperties> np, std::shared_ptr<PCAPWriter> pcapwriter, std::shared_ptr<ConfigReader> confreader) {
    this->np = np;
    this->time_sec = 0;
    this->time_us = 0;
    this->pcapwriter = pcapwriter;
    this->confreader = confreader;
}



/*
receiver redirecting to pcap
*/

void NetworkNodeSimulator::receive_message(std::vector<unsigned char> data, uint32_t time_s, uint32_t time_us) {
    this->pcapwriter->write_packet(data, time_s, time_us);
}

/*
receiver redirecting to ethernet
*/
void NetworkNodeSimulator::receive_message(std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<EthernetFrameInterface> initial_protocol_state, uint32_t time_s, uint32_t time_us) {
    std::shared_ptr<EthernetEvent> e = std::shared_ptr<EthernetEvent>(new EthernetEvent);
    std::shared_ptr<EthernetFrameInterface> etherframe = initial_protocol_state;
    etherframe->set_payload(payload);

    e->set_ethernet_frame(etherframe);
    e->set_event_rules({EthernetEventRulePtr(new SendEthernetData)});

    scheduler->schedule(e, time_s, time_us);
}

void NetworkNodeSimulator::receive_message(std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<IPv4PacketInterface> initial_protocol_state, uint32_t time_s, uint32_t time_us) {
    std::shared_ptr<IPv4Event> e = std::shared_ptr<IPv4Event>(new IPv4Event);
    std::shared_ptr<IPv4PacketInterface> packet = initial_protocol_state;
    packet->set_payload(payload);

    // packet->set_payload(c);
    packet->set_source({0x1, 0x2, 0x3,0x4}); // determined by generator file
    packet->set_destination({0x4, 0x3, 0x2, 0x1});
    // packet->set_time_to_live(64); // determined by host (generator file)

    e->set_ipv4_packet(packet, LinkLayer::Ethernet);
    e->set_event_rules({std::shared_ptr<IPv4EventRule>(new SendIPv4Data)});
    scheduler->schedule(e, time_s, time_us);
}

/*
receiver redirecting to tcp
*/
void NetworkNodeSimulator::receive_message(std::shared_ptr<TCPState> client, std::shared_ptr<TCPState> server, uint32_t time_s, uint32_t time_us) {
    std::shared_ptr<TCPEvent> e = std::shared_ptr<TCPEvent>(new TCPEvent(client, server, np->get_nlayer()));


    // packet->set_payload(c);
    // packet->set_source({0x1, 0x2, 0x3,0x4}); // determined by generator file
    // packet->set_destination({0x4, 0x3, 0x2, 0x1});
    // packet->set_time_to_live(64); // determined by host (generator file)

    e->set_event_rules({std::shared_ptr<TCPEventRule>(new SendSyn)});
    scheduler->schedule(e, time_s, time_us);
}