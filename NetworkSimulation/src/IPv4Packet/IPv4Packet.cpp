#include "IPv4Packet.h"
#include <stdexcept>
#include <cassert>
#include <algorithm>

void IPv4Packet::set_version() {
    unsigned char wanted_version = 4;
    this->version_ihl &= wanted_version<<4; // set version at 4 upper bits
}

void IPv4Packet::set_ihl() {
    this->version_ihl &= 5; // always 5 w/o options
}

void IPv4Packet::set_dscp(unsigned char dscp) {
    if (dscp > (1<<6)-1) { // dscp values are between 0-63
        throw std::invalid_argument("DSCP values must be between 0-63");
    }
    assert(dscp <= (1<<6)-1);

    this->dscp_ecn &= ~(((1<<6)-1)<<2); // clear upper 6 bits
    this->dscp_ecn |= (dscp << 2); // set upper 6 bits
}

void IPv4Packet::set_ecn(unsigned char ecn) {
    if (ecn > (1<<2)-1) { // dscp values are between 0-3
        // throw exception
    }
    assert(ecn <= (1<<2)-1);

    this->dscp_ecn |= ecn; // dscp occupy upper 6 bits

    assert(dscp_ecn & ((1<<2)-1) == ecn); // reading the two lower bits should give ecn
}

void IPv4Packet::set_total_length() {
    int calc_total_length = 0;
    if (this->get_payload()) {
        calc_total_length = this->get_payload()->to_array().size() + this->get_ihl();
    }

    this->total_length = {
        (unsigned char) calc_total_length, // lower bits
        (unsigned char) (calc_total_length>>8)}; // upper bits
}

void IPv4Packet::set_identification(int prev_id) {
    this->identification = {
        (unsigned char) prev_id,
        (unsigned char) (prev_id >> 8)
    };
}

void IPv4Packet::set_df_flag(bool b) {
    if (b) {
        this->flags_fragment_offset[0] |= 1<<6; // set 6th lsb
    } else {
        this->flags_fragment_offset[0] &= ~(1<<6); // clear 6th lsb
    }
}

void IPv4Packet::set_mf_flag(bool b) {
    if (b) {
        this->flags_fragment_offset[0] |= 1<<5; // set 6th lsb
    } else {
        this->flags_fragment_offset[0] &= ~(1<<5); // clear 6th lsb
    }
}

void IPv4Packet::set_fragment_offset(unsigned int offset) {
    if (offset > (1<<13)-1) { // i.e. offset > 2^13-1 => more than 13 bits present
        throw std::invalid_argument("Offset must be between 0 and 8191");
    }
    flags_fragment_offset[0] &= ~((1<<5)-1);

    this->flags_fragment_offset = {
        (unsigned char) ((offset >> 16) | flags_fragment_offset[0]),
        (unsigned char) (offset >> 8),
        (unsigned char) offset
    };
}

void IPv4Packet::set_time_to_live(unsigned char time_to_live) {
    this->time_to_live = time_to_live;
}

void IPv4Packet::set_protocol(unsigned char protocol) {
    this->protocol = protocol;
}

void IPv4Packet::set_header_checksum() {
    // std::vector<unsigned char> as_arr = to_array();
    // int sum = 0;
    // int i = 0;
    // while (i+1 < as_arr.size()) { // 16 bit sum
    //     sum += (((int)as_arr[i]) << 8) + as_arr[i+1];
    //     i++;
    // }
    // if (i < as_arr.size()) {
    //     sum += 
    // }
    this->header_checksum = {0x10, 0x20}; 
}

unsigned char IPv4Packet::get_dscp() {
    return this->dscp_ecn >> 2;
}

unsigned char IPv4Packet::get_ecn() {
    return this->dscp_ecn & ((1<<2)-1); // return 2 lsb
}

std::vector<unsigned char> IPv4Packet::to_array() {
    std::vector<unsigned char> header;

	auto add_to_header = [&header](unsigned char elem) -> void {
		header.push_back(elem);
	};
    add_to_header(version_ihl);
    add_to_header(dscp_ecn);
    std::for_each(this->total_length.begin(), this->total_length.end(), add_to_header);
    std::for_each(this->identification.begin(), this->identification.end(), add_to_header);
    std::for_each(this->flags_fragment_offset.begin(), this->flags_fragment_offset.end(), add_to_header);
    add_to_header(this->time_to_live);
    add_to_header(this->protocol);
    std::for_each(this->header_checksum.begin(), this->header_checksum.end(), add_to_header);
    std::for_each(this->source.begin(), this->source.end(), add_to_header);
    std::for_each(this->destination.begin(), this->destination.end(), add_to_header);

    return header;
}