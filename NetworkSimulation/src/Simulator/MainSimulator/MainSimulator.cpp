#include "MainSimulator.h"
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
#include <pcap/pcap.h>
#include <iostream>

std::shared_ptr<BaseScheduler> MainSimulator::get_next_scheduler() {
    std::shared_ptr<BaseScheduler> next_scheduler = nullptr;
    uint64_t next_time = std::numeric_limits<uint64_t>::max();
    for (auto scheduler : schedulers) {
        if (scheduler->contains_events()) {
            if (scheduler->get_scheduler_time() < next_time) {
                next_time = scheduler->get_scheduler_time();
                next_scheduler = scheduler;
            }
        }
    }
    return next_scheduler;
}

void MainSimulator::initialize() {
    scheduler_ethernet = std::shared_ptr<BaseScheduler>(new BaseScheduler());
    scheduler_ethernet->set_parent(shared_from_this());

    scheduler_ipv4 = std::shared_ptr<BaseScheduler>(new BaseScheduler());
    scheduler_ipv4->set_parent(shared_from_this());

    scheduler_tcp = std::shared_ptr<BaseScheduler>(new BaseScheduler());
    scheduler_tcp->set_parent(shared_from_this());

    schedulers = {scheduler_tcp, scheduler_ipv4, scheduler_ethernet};
}

void MainSimulator::run() {
    std::shared_ptr<BaseScheduler> s = get_next_scheduler();
    while(s != nullptr) {
        s->dispatch_next_event();

        s = get_next_scheduler();

    }
}

MainSimulator::MainSimulator(std::shared_ptr<NetworkProperties> np) {
    this->np = np;

    this->time = 0;
}



/*
receiver redirecting to pcap
*/

void MainSimulator::receive_message(std::vector<unsigned char> data, uint64_t time) {
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 1 << 16);
    pcap_dumper_t *dumper = pcap_dump_open(handle, "./test.pcap");

    
    struct pcap_pkthdr pcap_hdr;
    struct timeval timestamp;
    timestamp.tv_sec = 0;
    timestamp.tv_usec = time;

    pcap_hdr.caplen = data.size();
    pcap_hdr.len = pcap_hdr.caplen;
    pcap_hdr.ts = timestamp;

    pcap_dump((u_char *)dumper, &pcap_hdr, data.data());

    pcap_dump_close(dumper);
}

/*
receiver redirecting to ethernet
*/
void MainSimulator::receive_message(std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<EthernetFrameInterface> initial_protocol_state, uint64_t time) {
    std::shared_ptr<EthernetEvent> e = std::shared_ptr<EthernetEvent>(new EthernetEvent);
    std::shared_ptr<EthernetFrameInterface> etherframe = initial_protocol_state;
    etherframe->set_payload(payload);

    e->set_ethernet_frame(etherframe);
    e->set_event_rules({EthernetEventRulePtr(new SendEthernetData)});

    scheduler_ethernet->schedule(e, 0);
}

void MainSimulator::receive_message(std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<IPv4PacketInterface> initial_protocol_state, uint64_t time) {
    std::shared_ptr<IPv4Event> e = std::shared_ptr<IPv4Event>(new IPv4Event);
    std::shared_ptr<IPv4PacketInterface> packet = initial_protocol_state;
    packet->set_payload(payload);

    // packet->set_payload(c);
    packet->set_source({0x1, 0x2, 0x3,0x4}); // determined by generator file
    packet->set_destination({0x4, 0x3, 0x2, 0x1});
    // packet->set_time_to_live(64); // determined by host (generator file)

    e->set_ipv4_packet(packet, LinkLayer::Ethernet);
    e->set_event_rules({std::shared_ptr<IPv4EventRule>(new SendIPv4Data)});
    scheduler_ipv4->schedule(e, 0);
}

/*
receiver redirecting to tcp
*/
void MainSimulator::receive_message(std::shared_ptr<TCPState> client, std::shared_ptr<TCPState> server, uint64_t time) {
    std::shared_ptr<TCPEvent> e = std::shared_ptr<TCPEvent>(new TCPEvent(client, server, np->get_nlayer()));


    // packet->set_payload(c);
    // packet->set_source({0x1, 0x2, 0x3,0x4}); // determined by generator file
    // packet->set_destination({0x4, 0x3, 0x2, 0x1});
    // packet->set_time_to_live(64); // determined by host (generator file)

    e->set_event_rules({std::shared_ptr<TCPEventRule>(new SendSyn)});
    scheduler_tcp->schedule(e, time);
}