

/*
 * TCPConnection.h
 *
 *  Created on: 05 Nov 2023
 *      Author: erik
 */

#ifndef TCPCONNECTION_H_
#define TCPCONNECTION_H_

#include "../TCPSegment/TCPSegmentInterface.h"
#include <memory>

class TCPConnection {
private:
	std::shared_ptr<TCPSegmentInterface> client_state;
	std::shared_ptr<TCPSegmentInterface> server_state;
    uint64_t timestamp;
	uint16_t prop_delay;
	std::vector<std::tuple<uint64_t, std::shared_ptr<TCPSegmentInterface>>> segment_trace_client;
    std::vector<std::tuple<uint64_t, std::shared_ptr<TCPSegmentInterface>>> segment_trace_server;

public:
	TCPConnection(uint16_t client_source_port, uint16_t client_destination_port, uint64_t timestamp);
	void add_segment_to_client_trace(std::shared_ptr<TCPSegmentInterface> segment);
    void add_segment_to_server_trace(std::shared_ptr<TCPSegmentInterface> segment);
	void set_init_syn_packet();
	void set_syn_ack_packet();
	void set_ack_packet();
	void set_data_packet(std::shared_ptr<TCPSegmentInterface> segment);
	void do_succesfull_transmit(double packet_failure_prob, std::shared_ptr<TCPSegmentInterface> segment);
	void three_way_handshake();
	void send_data(int packetnr_client, int packetnr_server);

	std::vector<std::tuple<uint64_t, std::shared_ptr<TCPSegmentInterface>>> get_segment_trace_client() {return segment_trace_client;}
    std::vector<std::tuple<uint64_t, std::shared_ptr<TCPSegmentInterface>>> get_segment_trace_server() {return segment_trace_server;}
};


#endif /*TCPCONNECTION_H_*/