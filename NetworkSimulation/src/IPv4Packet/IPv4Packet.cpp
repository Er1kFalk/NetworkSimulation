#include "IPv4Packet.h"

void IPv4Packet::set_version() {
    this->version = 4;
}

void IPv4Packet::set_ihl() {
    this->ihl = 5; // always 5 w/o options
}

void IPv4Packet::set_type_of_service(TrafficClassInterface *t) {
    this->type_of_service = t;
}

void IPv4Packet::set_total_length() {
    int calc_total_length = this->get_payload()->to_array().size() + (int) this->ihl;
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
        this->df_flag = 1;
    } else {
        this->df_flag = 0;
    }
}

void IPv4Packet::set_mf_flag(bool b) {
    if (b) {
        this->mf_flag = 1;
    } else {
        this->mf_flag = 0;
    }
}

void IPv4Packet::set_fragment_offset(int offset) {
    this->offset = {
        (unsigned char) offset,
        (unsigned char) (offset >> 8),
        (unsigned char) (offset >> 16)
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

std::vector<unsigned char> IPv4Packet::to_array() {
    std::vector<unsigned char> header_arr;
    unsigned char version_ihl = 0;
    version_ihl = version_ihl | (((unsigned char) (this->version))<<4);
    version_ihl = version_ihl | ihl;
    
    unsigned char flag_offset_tail = (offset[0] | (((unsigned char) df_flag) << 5)) | (((unsigned char) mf_flag) << 6);

    header_arr.push_back(version_ihl);
    header_arr.push_back(this->type_of_service->get_ds_ecn());
    for (unsigned char c : total_length) {
        header_arr.push_back(c);
    }

    for (unsigned char c : identification) {
        header_arr.push_back(c);
    }
    header_arr.push_back(flag_offset_tail);
    header_arr.push_back(this->offset[1]);
    header_arr.push_back(this->offset[2]);
    header_arr.push_back(this->time_to_live);
    header_arr.push_back(this->protocol->get_protocol());
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