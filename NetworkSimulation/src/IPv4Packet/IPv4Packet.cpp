#include "IPv4Packet.h"
#include <stdexcept>

void IPv4Packet::set_version() {
    unsigned char wanted_version = 4;
    this->version_ihl &= wanted_version<<4; // set version at 4 upper bits
}

void IPv4Packet::set_ihl() {
    this->version_ihl &= 5; // always 5 w/o options
}

void IPv4Packet::set_type_of_service(TrafficClassInterface *t) {
    this->type_of_service = t;
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
        this->flags |= 1<<1; // set 2nd lsb
    } else {
        this->flags &= ~(1<<1); // clear 2nd lsb
    }
}

void IPv4Packet::set_mf_flag(bool b) {
    if (b) {
        this->flags |= 1; // set 1st lsb
    } else {
        this->flags &= ~1; // clear 1st lsb
    }
}

void IPv4Packet::set_fragment_offset(unsigned int offset) {
    if (offset > (1<<13)-1) { // i.e. offset > 2^13-1 => more than 13 bits present
        throw std::invalid_argument("Offset must be between 0 and 8191");
    }
    this->fragment_offset = {
        (unsigned char) (offset >> 16),
        (unsigned char) (offset >> 8),
        (unsigned char) offset
    };
}

void IPv4Packet::set_time_to_live(unsigned char time_to_live) {
    this->time_to_live = time_to_live;
}

void IPv4Packet::set_protocol(ProtocolTypeInterface *p) {
    this->protocol = p;
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

void IPv4Packet::set_source(IPv4AddressInterface *address) {
    this->source = address;
}

void IPv4Packet::set_destination(IPv4AddressInterface *address) {
    this->destination = address;
}

std::array<unsigned char, 3> IPv4Packet::get_flags_fragment_offset() {
    std::array<unsigned char, 3> get_flags_fragment_offset = this->fragment_offset;
    get_flags_fragment_offset[0] |= (flags<<5); // move the 3 lsb (where flags are stored) up to the 3 msb of the byte
    return get_flags_fragment_offset;
}

std::vector<unsigned char> IPv4Packet::to_array() {
    std::vector<unsigned char> header_arr;
    
    std::array<unsigned char, 3> flag_offset = get_flags_fragment_offset();

    header_arr.push_back(this->version_ihl);
    header_arr.push_back(this->type_of_service->get_traffic_class_as_char());
    for (unsigned char c : total_length) {
        header_arr.push_back(c);
    }

    for (unsigned char c : identification) {
        header_arr.push_back(c);
    }
    for (unsigned char c : flag_offset) {
        header_arr.push_back(c);
    }
    header_arr.push_back(this->time_to_live);
    header_arr.push_back(this->protocol->get_protocol_as_char());
    for (unsigned char c : header_checksum) {
        header_arr.push_back(c);
    }
    for (unsigned char c : source->get_address()) {
        header_arr.push_back(c);
    }
    for (unsigned char c : destination->get_address()) {
        header_arr.push_back(c);
    }
    return header_arr;
}