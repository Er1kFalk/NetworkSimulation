#include "IPv4EventRule.h"
#include "IPv4Event.h"
#include "../../IPv4Packet/IPv4PacketInterface.h"
#include "../../EthernetFrame/EthernetFrame.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../NetworkNodeSimulator/NetworkNodeSimulator.h"

void ReceiveIPv4Data::handle(IPv4EventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<IPv4PacketInterface> packet = e->get_ipv4_packet();
    
}

void SendIPv4DataClient::handle(IPv4EventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<IPv4PacketInterface> packet = e->get_ipv4_packet();
    packet->set_version();
    packet->set_identification(0); // should be random
    packet->set_mf_flag(false); // ip - if df = 0
    packet->set_fragment_offset(0);
    
    if (e->get_transmitter() == Transmitter::Client) {
        packet->set_source(e->get_genfile()->client.ip_info.ip_address);
        packet->set_destination(e->get_genfile()->server.ip_info.ip_address);
    } else {
        packet->set_source(e->get_genfile()->server.ip_info.ip_address);
        packet->set_destination(e->get_genfile()->client.ip_info.ip_address);
    }


    packet->recalculate_fields();


    // to ethernet
}

void PassIPv4DataToEthernet::handle(IPv4EventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<EthernetFrameInterface> etherframe = std::shared_ptr<EthernetFrameInterface>(new EthernetFrame());
    etherframe->set_ethertype({0x08, 0x00});

    scheduler->get_parent()->receive_message(e, e->get_ipv4_packet()->copy(), etherframe, 0, 0);
}
