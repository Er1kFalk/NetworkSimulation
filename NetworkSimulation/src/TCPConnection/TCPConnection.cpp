#include "TCPConnection.h"
#include <math.h>
#include <random>
#include "../TCPSegment/TCPSegment.h"
#include "../ArrayUtils/ArrayUtils.h"
#include <iostream>

TCPConnection::TCPConnection(uint16_t client_source_port, uint16_t client_destination_port, uint64_t timestamp) {
	srand(time(NULL));
    this->timestamp = timestamp;
	this->prop_delay = 10;
	client_state = std::shared_ptr<TCPSegmentInterface>(new TCPSegment);
	server_state = std::shared_ptr<TCPSegmentInterface>(new TCPSegment);

	client_state->set_source_port(client_source_port); // random
	client_state->set_destination_port(client_destination_port);
	client_state->set_sequence_nr(231321); // random
    client_state->set_window_size(65465);

	server_state->set_source_port(client_destination_port);
	server_state->set_destination_port(client_source_port);
	server_state->set_sequence_nr(231321); // random
    server_state->set_window_size(65465);
}

void TCPConnection::add_segment_to_client_trace(std::shared_ptr<TCPSegmentInterface> segment) {
    std::shared_ptr<TCPSegmentInterface> s = segment->copy();
    s->set_data_offset();
	segment_trace_client.push_back({timestamp, s});
	timestamp += prop_delay;
}

void TCPConnection::add_segment_to_server_trace(std::shared_ptr<TCPSegmentInterface> segment) {
	std::shared_ptr<TCPSegmentInterface> s = segment->copy();
    s->set_data_offset();
	segment_trace_server.push_back({timestamp, s});
	timestamp += prop_delay;
}

void TCPConnection::set_init_syn_packet() {
	client_state->set_syn_flag(true);
	client_state->set_ack_flag(false);
	client_state->set_acknowledgement_nr(0);
}

void TCPConnection::set_syn_ack_packet() {
	server_state->set_acknowledgement_nr(client_state->get_sequence_nr() + 1);
	server_state->set_syn_flag(true);
	server_state->set_ack_flag(true);
}

void TCPConnection::set_ack_packet() {
	client_state->set_acknowledgement_nr(server_state->get_sequence_nr() + 1);
    client_state->set_sequence_nr(client_state->get_sequence_nr() + 1);
	client_state->set_syn_flag(false);
	client_state->set_ack_flag(true);
}

void TCPConnection::set_data_packet(std::shared_ptr<TCPSegmentInterface> segment) {
	int mss = 1440;
	segment->set_ack_flag(true);
	segment->set_syn_flag(false);
	segment->set_payload(std::shared_ptr<CommunicationProtocol>(new Data(ArrayUtils::get_random_vector(mss))));
}

void TCPConnection::do_succesfull_transmit(double packet_failure_prob, std::shared_ptr<TCPSegmentInterface> segment) {
	int random = rand();
	add_segment_to_client_trace(segment);
	while (random <= (int) ceil(packet_failure_prob*(double) RAND_MAX)) { // transmit until successfull
		add_segment_to_client_trace(segment);
		random = rand();
	}
}

void TCPConnection::three_way_handshake() {
	double packet_failure_prob = 0.01;
	set_init_syn_packet();
	do_succesfull_transmit(packet_failure_prob, client_state);
	set_syn_ack_packet();
	add_segment_to_server_trace(server_state);
	set_ack_packet();
	do_succesfull_transmit(packet_failure_prob, client_state);
}

void TCPConnection::send_data(int packetnr_client, int packetnr_server) {
	double packet_failure_prob = 0.01;
	for (int i = 0; i < packetnr_client; i++) {
        client_state->set_sequence_nr(server_state->get_acknowledgement_nr());
        set_data_packet(client_state);
		add_segment_to_client_trace(client_state);

        server_state->set_ack_flag(true);
        server_state->set_syn_flag(false);
		server_state->set_acknowledgement_nr(server_state->get_acknowledgement_nr() + client_state->get_payload()->header_payload_to_array().size());
		add_segment_to_server_trace(server_state);
	}

	for (int i = 0; i < packetnr_server; i++) {
        server_state->set_sequence_nr(client_state->get_acknowledgement_nr());
		set_data_packet(server_state);
		add_segment_to_server_trace(server_state);

        client_state->set_payload(nullptr);
        client_state->set_ack_flag(true);
        client_state->set_syn_flag(false);
		client_state->set_acknowledgement_nr(client_state->get_acknowledgement_nr() + server_state->get_payload()->header_payload_to_array().size());
		add_segment_to_client_trace(client_state);
	}
}