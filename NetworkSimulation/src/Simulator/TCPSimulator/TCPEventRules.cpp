#include "TCPEventRules.h"
#include "TCPEvent.h"
#include "../../TCPSegment/TCPSegment.h"
#include <stdlib.h>
#include "../../IPv4Packet/IPv4Packet.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../MainSimulator/MainSimulator.h"
#include "../../RandomUtils/RandomUtils.h"

// void R_INIT_CONNECTION::handle(TCPEventPtr e) {

//     TCPEventPtr send_syn_event = TCPEventPtr(new TCP_SEND_SYN(e->get_current_client_state(), e->get_current_server_state()));
//     TCPScheduler::schedule(send_syn_event, {std::make_shared<std::function<void(TCPEventPtr)>>(f)}, 0);
// }

void SendSyn::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<RandomUtils> generator = std::shared_ptr<RandomUtils>(new RandomUtils());
    std::shared_ptr<TCPSegmentInterface> syn_segment = e->get_current_client_state()->get_current_segment();

    syn_segment->set_syn_flag(true);
    syn_segment->set_ack_flag(false);
	syn_segment->set_ack_nr(0);
    uint32_t seqnr = generator->generate_uniform_number() * (double) ((1ul<<32)-1);
    syn_segment->set_seq_nr(seqnr);
    syn_segment->set_ipv4_pseudo_header({0x1, 0x2, 0x3,0x4}, {0x4, 0x3, 0x2, 0x1}); // determined by generator file
    syn_segment->recalculate_fields();

    e->set_tx(Transmitter::Client);
    //e->set_current_client_state(syn_segment);

    // delay stuff
    int rtt = scheduler->get_parent()->get_np()->get_rtt();
    // scheduler->schedule(e->copy(), {TCPEventRulePtr(new ReceiveSynAck)}, rtt);
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
    syn_ack_segment->set_ack_nr(current_client_state->get_sequence_nr() + 1);
	syn_ack_segment->set_syn_flag(true);
	syn_ack_segment->set_ack_flag(true);

    e->set_tx(Transmitter::Server);

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

    current_client_state->set_ack_nr(current_server_state->get_sequence_nr() + 1);
    current_client_state->set_seq_nr(current_client_state->get_sequence_nr() + 1);
	current_client_state->set_syn_flag(false);
	current_client_state->set_ack_flag(true);

    e->set_tx(Transmitter::Client);

    // send to ipv4
}


void PassClientStateToIPv4::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<IPv4PacketInterface> packet = std::shared_ptr<IPv4PacketInterface>(new IPv4Packet);
    packet->set_version();
    packet->set_dscp(0);
    packet->set_ecn(0);
        
    
    packet->set_df_flag(true);
    
    packet->set_protocol(0x06); // determined by upper layer protocol

    scheduler->get_parent()->receive_message(e->get_current_client_state()->get_current_segment()->copy(), packet, 0);
}

void PassServerStateToIPv4::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr<IPv4PacketInterface> packet = std::shared_ptr<IPv4PacketInterface>(new IPv4Packet);
    packet->set_version();
    packet->set_dscp(0);
    packet->set_ecn(0);
    
    packet->set_df_flag(true);
    
    packet->set_protocol(0x06); // determined by upper layer protocol

    scheduler->get_parent()->receive_message(e->get_current_server_state()->get_current_segment()->copy(), packet, 0);
}