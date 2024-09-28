#include "IPv4EventRule.h"
#include "IPv4Event.h"
#include "../../../../HeaderGenerators/IPv4Packet/IPv4PacketInterface.h"
#include "../../../../HeaderGenerators/EthernetFrame/EthernetFrame.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../../NetworkNodeSimulator.h"

void ReceiveIPv4Data::handle(IPv4EventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<IPv4PacketInterface> packet = e->get_ipv4_packet();
    
}

void SendIPv4DataClient::handle(IPv4EventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<IPv4PacketInterface> packet = e->get_ipv4_packet();
    packet->set_version();
    packet->set_identification(0); // should be random
    packet->set_mf_flag(false); // ip - if df = 0
    packet->set_fragment_offset(0);
    
    auto genfile = e->get_parent()->get_generatorfile_by_id(e->get_id());

    if (e->get_transmitter() == GFStructs::TransmittingNow::Client) {
        packet->set_source(genfile.client.ip_info.ip_address);
        packet->set_destination(genfile.server.ip_info.ip_address);
        packet->set_time_to_live(genfile.client.ip_info.ttl_values);
    } else {
        packet->set_source(genfile.server.ip_info.ip_address);
        packet->set_destination(genfile.client.ip_info.ip_address);
        packet->set_time_to_live(genfile.server.ip_info.ttl_values);
    }


    packet->recalculate_fields();


    // to ethernet
}

void PassIPv4DataToEthernet::handle(IPv4EventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<EthernetFrameInterface> etherframe = std::shared_ptr<EthernetFrameInterface>(new EthernetFrame());
    etherframe->set_ethertype({0x08, 0x00});

    e->get_parent()->receive_message(e, e->get_ipv4_packet()->copy(), etherframe, 0, 0);
}
