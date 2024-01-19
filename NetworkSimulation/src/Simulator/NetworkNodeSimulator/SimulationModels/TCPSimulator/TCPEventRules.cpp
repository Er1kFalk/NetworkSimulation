#include "TCPEventRules.h"
#include "TCPEvent.h"
#include "../../../../HeaderGenerators/TCPSegment/TCPSegment.h"
#include <stdlib.h>
#include "../../../../HeaderGenerators/IPv4Packet/IPv4Packet.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../../NetworkNodeSimulator.h"
#include "../../../../UtilityLibraries/RandomUtils/RandomUtils.h"
#include "../BaseScheduler/EventTypeDefs.h"
#include "../IPv4Simulator/IPv4Event.h"
#include "../IPv4Simulator/IPv4EventRule.h"
#include "../../../../HeaderGenerators/Data/Data.h"



std::shared_ptr<RandomUtils> TCPEventRule::generator = std::shared_ptr<RandomUtils>(new RandomUtils());

void TCPEventRule::send_data(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    if (!e->send_queue_empty()) {
        TCPEventPtr tcpevent = e;
        GFStructs::TransmittingNow t = tcpevent->send_order_see_first();
        if (t == GFStructs::TransmittingNow::Client) {
            tcpevent->set_event_rules({TCPEventRulePtr(new ClientSendData)});
            uint32_t interpacket_delay = tcpevent->get_current_client_state()->interpacket_delays_see_first();
            scheduler->schedule(tcpevent, 0, interpacket_delay);
            tcpevent->get_current_client_state()->remove_from_interpacket_delays();
            tcpevent->remove_from_send_order();
        } else if (t == GFStructs::TransmittingNow::Server) {
            tcpevent->set_event_rules({TCPEventRulePtr(new ServerSendData)});
            uint32_t interpacket_delay = tcpevent->get_current_server_state()->interpacket_delays_see_first();
            scheduler->schedule(tcpevent, 0, interpacket_delay);
            tcpevent->get_current_server_state()->remove_from_interpacket_delays();
            tcpevent->remove_from_send_order();
        }
        
    }
}


void SendSyn::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
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
    e->get_current_client_state()->set_initial_seqnr(seqnr);
    e->get_current_client_state()->add_bytes_sent(1);
    e->get_current_server_state()->add_bytes_received(1);
    client->set_sequence_nr(seqnr);

    client->add_mss_option(genfile.client.tcp_info.mss);
    uint32_t choose_index = generator->generate_uniform_number() * (double) (genfile.client.tcp_info.window_sizes.size()-1);
    client->set_window_size(genfile.client.tcp_info.window_sizes[choose_index]);
    client->recalculate_fields();

    e->set_transmitter(GFStructs::TransmittingNow::Client);

    uint32_t rtt = scheduler->get_parent()->get_np()->get_rtt()*1000.0; // in microseconds

    TCPEventPtr tcpevent = e->copy();
    tcpevent->set_event_rules({TCPEventRulePtr(new ReceiveSynAck)});

    scheduler->schedule(tcpevent, 0, rtt);
   
}

void ReceiveSynAck::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    auto generator = std::shared_ptr<RandomUtils>(new RandomUtils());
    std::shared_ptr current_client_state = e->get_current_client_state()->get_current_segment();
    std::shared_ptr syn_ack_segment = e->get_current_server_state()->get_current_segment();
    
    uint32_t seqnr = generator->generate_uniform_number() * (double) ((1ul<<32)-1);
    e->get_current_server_state()->set_initial_seqnr(seqnr);
    syn_ack_segment->set_sequence_nr(seqnr);
    e->get_current_client_state()->add_bytes_received(1);
    e->get_current_server_state()->add_bytes_sent(1);

    auto genfile = scheduler->get_parent()->get_generatorfile_by_id(e->get_id());


    syn_ack_segment->set_acknowledgement_nr(e->get_current_server_state()->get_bytes_received() + e->get_current_client_state()->get_initial_seq_nr());
    syn_ack_segment->add_mss_option(genfile.server.tcp_info.mss);
	syn_ack_segment->set_syn_flag(true);
	syn_ack_segment->set_ack_flag(true);
    
    uint32_t choose_index = generator->generate_uniform_number() * (double) (genfile.server.tcp_info.window_sizes.size()-1);
    syn_ack_segment->set_window_size(genfile.server.tcp_info.window_sizes[choose_index]);

    syn_ack_segment->recalculate_fields();

    e->set_transmitter(GFStructs::TransmittingNow::Server);

    TCPEventPtr tcpevent = e->copy();
    assert(e.get() != tcpevent.get());
    tcpevent->set_event_rules({TCPEventRulePtr(new SendInitialAck)});

    scheduler->schedule(tcpevent, 0, 1000);
}

void SendInitialAck::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr current_client_state = e->get_current_client_state()->get_current_segment();
    std::shared_ptr current_server_state = e->get_current_server_state()->get_current_segment();

    current_client_state->set_acknowledgement_nr(e->get_current_client_state()->get_bytes_received() + e->get_current_server_state()->get_initial_seq_nr());

    current_client_state->set_syn_flag(false);
	current_client_state->set_ack_flag(true);
    current_client_state->set_options({}); // clear the option
    current_server_state->set_options({});

    auto generator = std::shared_ptr<RandomUtils>(new RandomUtils());
    auto genfile = scheduler->get_parent()->get_generatorfile_by_id(e->get_id());
    uint32_t choose_index = generator->generate_uniform_number() * (double) (genfile.client.tcp_info.window_sizes.size()-1);
    current_client_state->set_window_size(genfile.client.tcp_info.window_sizes[choose_index]);
    current_client_state->recalculate_fields();

    e->set_transmitter(GFStructs::TransmittingNow::Client);

    TCPEventRule::send_data(e, scheduler);
}

void SendData::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    
}

void ClientSendData::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr current_client_state = e->get_current_client_state()->get_current_segment();
    
    std::shared_ptr data = std::shared_ptr<Data>(new Data(e->get_current_client_state()->data_send_queue_see_first()));
    e->get_current_client_state()->remove_from_data_send_queue();
    current_client_state->set_payload(data);
    
    e->set_transmitter(GFStructs::TransmittingNow::Client);
    
    current_client_state->set_sequence_nr(e->get_current_client_state()->get_bytes_sent() + e->get_current_client_state()->get_initial_seq_nr());
    e->get_current_client_state()->add_bytes_sent(data->header_payload_to_array().size());
    e->get_current_server_state()->add_bytes_received(data->header_payload_to_array().size());
    
    current_client_state->set_psh_flag(true);
    current_client_state->recalculate_fields();

    TCPEventRule::send_data(e->copy(), scheduler);

    TCPEventPtr tcpevent = e->copy();
    tcpevent->set_event_rules({TCPEventRulePtr(new ServerSendAck)});
    uint32_t rtt = scheduler->get_parent()->get_np()->get_rtt()*1000.0;
    scheduler->schedule(tcpevent, 0, rtt);
}

void ServerSendData::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr current_server_state = e->get_current_server_state()->get_current_segment();


    // set the payload
    std::shared_ptr data = std::shared_ptr<Data>(new Data(e->get_current_server_state()->data_send_queue_see_first()));
    e->get_current_server_state()->remove_from_data_send_queue(); 
    current_server_state->set_payload(data);

    current_server_state->set_sequence_nr(e->get_current_server_state()->get_bytes_sent() + e->get_current_server_state()->get_initial_seq_nr());
    e->get_current_server_state()->add_bytes_sent(data->header_payload_to_array().size());
    e->get_current_client_state()->add_bytes_received(data->header_payload_to_array().size());


    // set fields    
    current_server_state->set_syn_flag(false);
    current_server_state->set_psh_flag(true);
    current_server_state->recalculate_fields();

    e->set_transmitter(GFStructs::TransmittingNow::Server);

    // schedule any data sending events, if needed
    TCPEventRule::send_data(e->copy(), scheduler);

    // schedule an ack event (by client)
    TCPEventPtr tcpevent = e->copy();
    tcpevent->set_event_rules({TCPEventRulePtr(new ClientSendAck)});
    uint32_t rtt = scheduler->get_parent()->get_np()->get_rtt()*1000.0;
    scheduler->schedule(tcpevent, 0, rtt);
}

void ServerSendAck::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr current_server_state = e->get_current_server_state()->get_current_segment();
    std::shared_ptr current_client_state = e->get_current_client_state()->get_current_segment();

    current_server_state->set_acknowledgement_nr(e->get_current_server_state()->get_bytes_received() + e->get_current_client_state()->get_initial_seq_nr());
    current_server_state->set_syn_flag(false);
    current_server_state->set_payload(nullptr);
    current_server_state->recalculate_fields();
    

    e->set_transmitter(GFStructs::TransmittingNow::Server);
}

void ClientSendAck::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    std::shared_ptr current_server_state = e->get_current_server_state()->get_current_segment();
    std::shared_ptr current_client_state = e->get_current_client_state()->get_current_segment();

    current_client_state->set_acknowledgement_nr(e->get_current_client_state()->get_bytes_received() + e->get_current_server_state()->get_initial_seq_nr());
    current_client_state->set_syn_flag(false);
    current_client_state->set_psh_flag(false);
    current_client_state->set_payload(nullptr);
    current_client_state->recalculate_fields();
    current_server_state->set_sequence_nr(e->get_current_server_state()->get_bytes_sent() + e->get_current_server_state()->get_initial_seq_nr());
    

    e->set_transmitter(GFStructs::TransmittingNow::Client);
}

void TCPReset::handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    e->get_current_client_state()->get_current_segment()->set_rst_flag(true);
    e->get_current_client_state()->get_current_segment()->set_fin_flag(true);

    auto genfile = scheduler->get_parent()->get_generatorfile_by_id(e->get_id());
    e->get_current_client_state()->get_current_segment()->set_ipv4_pseudo_header(genfile.client.ip_info.ip_address, genfile.server.ip_info.ip_address);
    e->get_current_client_state()->get_current_segment()->recalculate_fields();

    e->set_transmitter(GFStructs::TransmittingNow::Client);
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