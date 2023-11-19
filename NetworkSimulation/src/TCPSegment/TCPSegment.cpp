#include "TCPSegment.h"
#include "../BitOperations/BitOperations.h"
#include <iostream>
#include "../ProtocolUtils/ProtocolUtils.h"

void TCPSegment::set_ipv4_pseudo_header(std::array<unsigned char, 4> source_ip_address, std::array<unsigned char, 4> destination_ip_address) {
    this->source_ip_address = source_ip_address;
    this->destination_ip_address = destination_ip_address;
}

/*Setters*/

void TCPSegment::set_source_port(uint16_t port) {
    // sets elements 0-1 to source port value
    this->tcp_header = BitOperations::int16_into_char_vector(port, this->tcp_header, 0);
}

void TCPSegment::set_destination_port(uint16_t port) {
    // sets elements 2-3 to destination port value
    this->tcp_header = BitOperations::int16_into_char_vector(port, this->tcp_header, 2);
}

void TCPSegment::set_sequence_nr(uint32_t seq) {
    // sets elements 4-7 to seq value
    this->tcp_header = BitOperations::int32_into_char_vector(seq, this->tcp_header, 4);
}

void TCPSegment::set_ack_nr(uint32_t ack) {
    // sets elements 8-11 to ack value
    this->tcp_header = BitOperations::int32_into_char_vector(ack, this->tcp_header, 8);
}

void TCPSegment::set_data_offset() {
    const unsigned char header_length = 5;
    // set 4 upper bits to header length and lower 4 bits are left at 0
    const unsigned char data_offset_reserved = BitOperations::set_n_upper_bits(0, header_length, 4);
    
    this->tcp_header[12] = data_offset_reserved;
}

/* Flag setters*/

void TCPSegment::set_cwr_flag(bool b) {
    const unsigned char flags = this->tcp_header[13];
    this->tcp_header[13] = BitOperations::set_nth_lsb(flags, 7, b);
}

void TCPSegment::set_ece_flag(bool b) {
    const unsigned char flags = this->tcp_header[13];
    this->tcp_header[13] = BitOperations::set_nth_lsb(flags, 6, b);
}

void TCPSegment::set_urg_flag(bool b) {
    const unsigned char flags = this->tcp_header[13];
    this->tcp_header[13] = BitOperations::set_nth_lsb(flags, 5, b);
}

void TCPSegment::set_ack_flag(bool b) {
    const unsigned char flags = this->tcp_header[13];
    this->tcp_header[13] = BitOperations::set_nth_lsb(flags, 4, b);
}

void TCPSegment::set_psh_flag(bool b) {
    const unsigned char flags = this->tcp_header[13];
    this->tcp_header[13] = BitOperations::set_nth_lsb(flags, 3, b);
}

void TCPSegment::set_rst_flag(bool b) {
    const unsigned char flags = this->tcp_header[13];
    this->tcp_header[13] = BitOperations::set_nth_lsb(flags, 2, b);
}

void TCPSegment::set_syn_flag(bool b) {
    const unsigned char flags = this->tcp_header[13];
    this->tcp_header[13] = BitOperations::set_nth_lsb(flags, 1, b);
}

void TCPSegment::set_fin_flag(bool b) {
    const unsigned char flags = this->tcp_header[13];
    this->tcp_header[13] = BitOperations::set_nth_lsb(flags, 0, b);
}


void TCPSegment::set_window_size(uint16_t wsize) {
    // set index 14-15 to window size
    this->tcp_header = BitOperations::int16_into_char_vector(wsize, this->tcp_header, 14);
}

void TCPSegment::set_checksum() {
    std::vector<unsigned char> pseudo_header;
    for (unsigned char c : source_ip_address) {pseudo_header.push_back(c);}
    for (unsigned char c : destination_ip_address) {pseudo_header.push_back(c);}
    pseudo_header.push_back(0);
    pseudo_header.push_back(0x06);
    std::vector<unsigned char> tcplength = BitOperations::int16_into_char_vector(header_payload_to_array().size(), {0,0}, 0);
    for (unsigned char c : tcplength) {pseudo_header.push_back(c);}


    std::vector<unsigned char> payload_arr = {};   
    if (payload != nullptr) {
        payload_arr = this->payload->header_payload_to_array();
    }

    this->tcp_header = BitOperations::int16_into_char_vector(ProtocolUtils::calculate_internet_checksum(pseudo_header) + ProtocolUtils::calculate_internet_checksum(tcp_header) + ProtocolUtils::calculate_internet_checksum(payload_arr), this->tcp_header, 16);
}

void TCPSegment::set_urgent_pointer(uint16_t urgent_pointer) {
    // set index 18-19 to urgent pointer
    this->tcp_header = BitOperations::int16_into_char_vector(urgent_pointer, this->tcp_header, 18);

}


/*Getters*/

uint16_t TCPSegment::get_source_port() {
    // convert octet 0-1 to int
    return BitOperations::char_vector_to_int16(this->tcp_header, 0);
}

uint16_t TCPSegment::get_destination_port() {
    // convert octet 2-3 to int
    return BitOperations::char_vector_to_int16(this->tcp_header, 2);
}

uint32_t TCPSegment::get_sequence_nr() {
    // convert octet 4-7 to int
    return BitOperations::char_vector_to_int32(this->tcp_header, 4);
}

uint32_t TCPSegment::get_ack_nr() {
    // convert octet 8-11 to int
    return BitOperations::char_vector_to_int32(this->tcp_header, 8);
}

unsigned char TCPSegment::get_data_offset() {
    const unsigned char data_offset_reserved = this->tcp_header[12];
    return BitOperations::read_n_upper_bits(data_offset_reserved, 4);
}

bool TCPSegment::get_cwr_flag() {
    const unsigned char flags = this->tcp_header[13];
    return (bool) BitOperations::read_nth_lsb(flags, 7);
}
bool TCPSegment::get_ece_flag() {
    const unsigned char flags = this->tcp_header[13];
    return (bool) BitOperations::read_nth_lsb(flags, 6);
}
bool TCPSegment::get_urg_flag() {
    const unsigned char flags = this->tcp_header[13];
    return (bool) BitOperations::read_nth_lsb(flags, 5);
}
bool TCPSegment::get_ack_flag() {
    const unsigned char flags = this->tcp_header[13];
    return (bool) BitOperations::read_nth_lsb(flags, 4);
}
bool TCPSegment::get_psh_flag() {
    const unsigned char flags = this->tcp_header[13];
    return (bool) BitOperations::read_nth_lsb(flags, 3);
}
bool TCPSegment::get_rst_flag() {
    const unsigned char flags = this->tcp_header[13];
    return (bool) BitOperations::read_nth_lsb(flags, 2);
}
bool TCPSegment::get_syn_flag() {
    const unsigned char flags = this->tcp_header[13];
    return (bool) BitOperations::read_nth_lsb(flags, 1);
}
bool TCPSegment::get_fin_flag() {
    const unsigned char flags = this->tcp_header[13];
    return (bool) BitOperations::read_nth_lsb(flags, 0);
}

uint16_t TCPSegment::get_window_size() {
    return BitOperations::char_vector_to_int16(this->tcp_header, 14);
}

uint16_t TCPSegment::get_checksum() {
    return BitOperations::char_vector_to_int16(this->tcp_header, 16);
}

uint16_t TCPSegment::get_urgent_pointer() {
    return BitOperations::char_vector_to_int16(this->tcp_header, 18);
}

std::vector<unsigned char> TCPSegment::header_payload_to_array() {
    std::vector<unsigned char> header_payload = this->header_to_array();
    
    std::shared_ptr<CommunicationProtocol> it = this->payload;
    while (it != nullptr) {
		for (unsigned char c : it->header_to_array()) {
            header_payload.push_back(c);
        }
		it = it->get_payload();
	}

    return header_payload;
}

std::shared_ptr<TCPSegmentInterface> TCPSegment::copy() {
    return std::make_shared<TCPSegment>(*this);
}

void TCPSegment::recalculate_fields() {
    set_data_offset();
    set_checksum();
}