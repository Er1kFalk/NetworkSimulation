#include "TCPEventRules.h"
#include "TCPEvent.h"
#include "../../TCPSegment/TCPSegment.h"
#include <stdlib.h>
#include "../../IPv4Packet/IPv4Packet.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../NetworkNodeSimulator/NetworkNodeSimulator.h"
#include "../../RandomUtils/RandomUtils.h"
#include "../BaseScheduler/EventTypeDefs.h"
#include "../IPv4Simulator/IPv4Event.h"
#include "../IPv4Simulator/IPv4EventRule.h"

// void R_INIT_CONNECTION::handle(TCPEventPtr e) {

//     TCPEventPtr send_syn_event = TCPEventPtr(new TCP_SEND_SYN(e->get_current_client_state(), e->get_current_server_state()));
//     TCPScheduler::schedule(send_syn_event, {std::make_shared<std::function<void(TCPEventPtr)>>(f)}, 0);
// }

void SendSyn::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<RandomUtils> generator = std::shared_ptr<RandomUtils>(new RandomUtils());
    std::shared_ptr<TCPSegmentInterface> client = e->get_current_client_state()->get_current_segment();
    std::shared_ptr<TCPSegmentInterface> server = e->get_current_server_state()->get_current_segment();

    auto genfile = scheduler->get_parent()->get_generatorfile_by_id(e->get_id());

    client->set_source_port(genfile.client.tcp_info.source_port);
    client->set_destination_port(genfile.server.tcp_info.source_port);
    client->set_ipv4_pseudo_header(genfile.client.ip_info.ip_address, genfile.server.ip_info.ip_address);

    server->set_source_port(genfile.server.tcp_info.source_port);
    server->set_destination_port(genfile.client.tcp_info.source_port);
    server->set_ipv4_pseudo_header(genfile.server.ip_info.ip_address, genfile.client.ip_info.ip_address);


    client->set_syn_flag(true);
    client->set_ack_flag(false);
	client->set_acknowledgement_nr(0);
    uint32_t seqnr = generator->generate_uniform_number() * (double) ((1ul<<32)-1);
    client->set_sequence_nr(seqnr);
    client->add_mss_option(genfile.client.tcp_info.mss);
    client->recalculate_fields();

    e->set_transmitter(Transmitter::Client);
    //e->set_current_client_state(syn_segment);

    // delay stuff
    uint32_t rtt = scheduler->get_parent()->get_np()->get_rtt()*1000.0; // in microseconds

    TCPEventPtr tcpevent = e->copy();
    tcpevent->set_event_rules({TCPEventRulePtr(new ReceiveSynAck)});

    scheduler->schedule(tcpevent, 0, rtt);
    // send to ipv4

    // send to ipv4
    // if (np->is_packet_dropped()) { // retransmit
    //     uint64_t rto = e->get_current_client_state()->get_rto();
    //     scheduler->schedule(e, {TCPEventRulePtr(new SendSyn)}, rto); // + RTT
    //     e->get_current_client_state()->set_rto(2*rto);
    // } else { // receive
    //     int64_t rtt = np->get_rtt();
    //     if (!(e->get_current_client_state()->get_is_retransmission())) {
    //         if (!(e->get_current_client_state()->get_first_rtt_measurement_made())) {
    //             e->get_current_client_state()->set_srtt(rtt);
    //             e->get_current_client_state()->set_rttvar(rtt/2);
    //             e->get_current_client_state()->set_rto(rtt + 4*rtt/2);
    //             e->get_current_client_state()->set_first_rtt_measurement_made(true);
    //         } else {
    //             const int beta = 250; // 1/4s = 250ms
    //             const int alpha = 125; // 1/8s = 125ms
    //             int rttvar = e->get_current_client_state()->get_rttvar();
    //             int srtt = e->get_current_client_state()->get_srtt();

    //             e->get_current_client_state()->set_rttvar((1000-beta)*rttvar+beta*std::abs(srtt-rtt));
    //             e->get_current_client_state()->set_srtt((1000-alpha)*srtt + alpha*rtt);
    //         }
    //     }

    // schedule ipv4 event
}

void ReceiveSynAck::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr current_client_state = e->get_current_client_state()->get_current_segment();
    std::shared_ptr syn_ack_segment = e->get_current_server_state()->get_current_segment();
    syn_ack_segment->set_acknowledgement_nr(current_client_state->get_sequence_nr() + 1);
	syn_ack_segment->set_syn_flag(true);
	syn_ack_segment->set_ack_flag(true);
    syn_ack_segment->recalculate_fields();

    e->set_transmitter(Transmitter::Server);

    TCPEventPtr tcpevent = e->copy();
    assert(e.get() != tcpevent.get());
    tcpevent->set_event_rules({TCPEventRulePtr(new SendAck)});

    scheduler->schedule(tcpevent, 0, 100);


    // scheduler->schedule(e->copy(), {TCPEventRulePtr(new SendAck)}, 0);

    // send to ipv4

    // if (np->is_packet_dropped()) {
    //     scheduler->schedule(e, {TCPEventRulePtr(new SendSyn)}, 0);
    // } else {

    // }
}

void SendAck::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr current_client_state = e->get_current_client_state()->get_current_segment();
    std::shared_ptr current_server_state = e->get_current_server_state()->get_current_segment();

    current_client_state->set_acknowledgement_nr(current_server_state->get_sequence_nr() + 1);
    current_client_state->set_sequence_nr(current_client_state->get_sequence_nr() + 1);
	current_client_state->set_syn_flag(false);
	current_client_state->set_ack_flag(true);
    current_client_state->set_options({}); // clear the option
    current_client_state->recalculate_fields();

    e->set_transmitter(Transmitter::Client);

    // send to ipv4
}


void PassClientStateToIPv4::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<IPv4PacketInterface> packet = std::shared_ptr<IPv4PacketInterface>(new IPv4Packet);
    packet->set_dscp(0);
    packet->set_ecn(0);
    packet->set_df_flag(true);
    packet->set_protocol(0x06); // determined by upper layer protocol
    

    scheduler->get_parent()->receive_message(e, e->get_current_client_state()->get_current_segment()->copy(), packet, 0, 0);
}

void PassServerStateToIPv4::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<IPv4PacketInterface> packet = std::shared_ptr<IPv4PacketInterface>(new IPv4Packet);   
    packet->set_dscp(0);
    packet->set_ecn(0);
    packet->set_df_flag(true);
    packet->set_protocol(0x06); // determined by upper layer protocol

    scheduler->get_parent()->receive_message(e, e->get_current_server_state()->get_current_segment()->copy(), packet, 0, 0);
}