/*
 * TCPSegment.h
 *
 *  Created on: 31 Oct 2023
 *      Author: erik
 */

#ifndef TCPSEGMENT_H_
#define TCPSEGMENT_H_

#include "TCPSegmentInterface.h"
#include <array>
#include <vector>
#include <cassert>
class TCPSegment : public TCPSegmentInterface {
    std::vector<unsigned char> tcp_header;
    std::shared_ptr<CommunicationProtocol> payload;

public:
    TCPSegment() {
        this->tcp_header.resize(20); // default header size
        for (unsigned char& c : tcp_header) {
            c = 0; 
        }

        for (const unsigned char c : tcp_header) {
            assert(c == 0);
        }
    }

    /*Setters*/
    void set_source_port(uint16_t port) override;
    void set_destination_port(uint16_t port) override;
    void set_seq_nr(uint32_t seq) override;
    void set_ack_nr(uint32_t ack) override;
    void set_data_offset() override;

    void set_cwr_flag(bool b) override;
    void set_ece_flag(bool b) override;
    void set_urg_flag(bool b) override;
    void set_ack_flag(bool b) override;
    void set_psh_flag(bool b) override;
    void set_rst_flag(bool b) override;
    void set_syn_flag(bool b) override;
    void set_fin_flag(bool b) override;

    void set_window_size(uint16_t wsize) override;
    void set_checksum() override;
    void set_urgent_pointer(uint16_t urgent_pointer) override;

    /*getters*/
    uint16_t get_source_port() override;
    uint16_t get_destination_port() override;
    uint32_t get_sequence_nr() override;
    uint32_t get_ack_nr() override;
    unsigned char get_data_offset() override;

    bool get_cwr_flag() override;
    bool get_ece_flag() override;
    bool get_urg_flag() override;
    bool get_ack_flag() override;
    bool get_psh_flag() override;
    bool get_rst_flag() override;
    bool get_syn_flag() override;
    bool get_fin_flag() override;

    uint16_t get_window_size() override;
    uint16_t get_checksum() override;
    uint16_t get_urgent_pointer() override;

    std::vector<unsigned char> header_to_array() override {return this->tcp_header;}
    std::vector<unsigned char> header_payload_to_array() override;

    void set_payload(std::shared_ptr<CommunicationProtocol> payload) override {this->payload = payload;}
    std::shared_ptr<CommunicationProtocol> get_payload () override {return this->payload;}
    void recalculate_fields() override;
    std::shared_ptr<TCPSegmentInterface> copy();
};

#endif /* IPV4PACKET_H_ */
