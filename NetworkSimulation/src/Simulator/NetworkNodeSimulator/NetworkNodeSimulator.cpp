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

void NetworkNodeSimulator::initialize_tcp_event(uint32_t id, GFStructs::GeneratorFile gf) {
    auto client = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());
        auto server = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

        auto client_state = std::shared_ptr<TCPState>(new TCPState(client->copy()));
        auto server_state = std::shared_ptr<TCPState>(new TCPState(server->copy()));

        auto event = std::shared_ptr<TCPEvent>(new TCPEvent(client_state, server_state, NetworkLayer::IPv4));
        event->set_id(id);

        uint32_t j = gf.connection_offset_sec;
        while (j < this->max_gen_time) {
            auto to_schedule = event->copy();
            to_schedule->set_event_rules({TCPEventRulePtr(new SendSyn)});
            this->scheduler->schedule(to_schedule, j, time_us);
            j += gf.connection_offset_sec;
        }
}

void NetworkNodeSimulator::initialize() {
    scheduler = std::shared_ptr<BaseScheduler>(new BaseScheduler());
    scheduler->set_parent(shared_from_this());

    auto genfiles = confreader->get_generatorfiles();

    for (uint32_t i = 0; i < genfiles.size(); i++) {

        generatorfiles[i] = genfiles[i];

        for (uint32_t j = GFStructs::LayerModel::Application; j != GFStructs::LayerModel::Link; j++) {
            auto key = genfiles[i].protocol_stack.find(static_cast<GFStructs::LayerModel>(j));
            if (key != genfiles[i].protocol_stack.end()) {
                
                if (key->second == GFStructs::ProtocolModel::TCP) {
                    initialize_tcp_event(i, genfiles[i]);
                    
                } else if (key->second == GFStructs::ProtocolModel::IPv4) {
                    
                   
                } else if (key->second == GFStructs::ProtocolModel::Ethernet) {

                    
                } else {
                    continue;
                }
                break;
            } 
        }
        
    }
}

void NetworkNodeSimulator::run() {
    while(scheduler->contains_events()) {
        scheduler->dispatch_next_event();
    }
}

NetworkNodeSimulator::NetworkNodeSimulator(std::shared_ptr<NetworkProperties> np, std::shared_ptr<PCAPWriter> pcapwriter, std::shared_ptr<ConfigReader> confreader, uint32_t max_gen_time) {
    this->np = np;
    this->time_sec = 0;
    this->time_us = 0;
    this->pcapwriter = pcapwriter;
    this->confreader = confreader;
    this->max_gen_time = max_gen_time;
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
void NetworkNodeSimulator::receive_message(std::shared_ptr<Event> calling_event, std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<EthernetFrameInterface> initial_protocol_state, uint32_t time_s, uint32_t time_us) {
    std::shared_ptr<EthernetEvent> e = std::shared_ptr<EthernetEvent>(new EthernetEvent);
    std::shared_ptr<EthernetFrameInterface> etherframe = initial_protocol_state;
    etherframe->set_payload(payload);

    e->set_ethernet_frame(etherframe);
    e->set_event_rules({EthernetEventRulePtr(new SendEthernetData)});

    scheduler->schedule(e, time_s, time_us);
}

void NetworkNodeSimulator::receive_message(std::shared_ptr<Event> calling_event, std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<IPv4PacketInterface> initial_protocol_state, uint32_t time_s, uint32_t time_us) {
    std::shared_ptr<IPv4Event> e = std::shared_ptr<IPv4Event>(new IPv4Event);
    initial_protocol_state->set_payload(payload);


    e->set_ipv4_packet(initial_protocol_state);
    e->set_id(calling_event->get_id());
    e->set_transmitter(calling_event->get_transmitter());
    e->set_llayer(LinkLayer::Ethernet);
    e->set_event_rules({std::shared_ptr<IPv4EventRule>(new SendIPv4DataClient)});
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

GFStructs::GeneratorFile NetworkNodeSimulator::get_generatorfile_by_id(uint32_t id) {
    auto key = generatorfiles.find(id);
    if (key == generatorfiles.end()) {
        throw std::invalid_argument("No generator file by this id");
    } else {
        return key->second;
    }
}