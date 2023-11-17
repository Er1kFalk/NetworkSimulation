#include "IPv4Packet.h"
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include "../BitOperations/BitOperations.h"

const unsigned char IPv4Packet::default_header_size = 20; // IHL w/o options+padding (in octets, not in 32-bit blocks as IHL is measured in)
const unsigned char IPv4Packet::ip_version = 4;
void IPv4Packet::set_version() {
    // set upper 4 bits to wanted version
    this->version_ihl = BitOperations::set_n_upper_bits(this->version_ihl, ip_version, 4);
}

void IPv4Packet::set_ihl() {
    int octet_amount = this->default_header_size + this->options.size() + this->padding.size();
    assert(octet_amount % 4 == 0); // header should ALWAYS be a multiple 32 bits / 4 octets - if not, something is wrong
    // set 4 lower bits to the amount of 4-octet / 32bit values
    this->version_ihl = BitOperations::set_n_lower_bits(this->version_ihl, octet_amount/4, 4);
}

void IPv4Packet::set_dscp(unsigned char dscp) {
    if (dscp > (1<<6)-1) { // dscp values are between 0-63
        throw std::invalid_argument("DSCP values must be between 0-63");
    }
    assert(dscp <= 63);

    // set 6 upper bits to dscp
    this->dscp_ecn = BitOperations::set_n_upper_bits(this->dscp_ecn, dscp, 6);
}

void IPv4Packet::set_ecn(unsigned char ecn) {
    if (ecn > (1<<2)-1) { // dscp values are between 0-3
        throw std::invalid_argument("ECN values must be between 0-3");
    }
    assert(ecn <= (1<<2)-1);

    // set 2 lower bits to ecn
    this->dscp_ecn = BitOperations::set_n_lower_bits(this->dscp_ecn, ecn, 2);

    assert(dscp_ecn & ((1<<2)-1) == ecn); // reading the two lower bits should give ecn
}

void IPv4Packet::set_total_length() {
    // it is at least the header size
    int calc_total_length = this->default_header_size + this->options.size() + this->padding.size();
    if (this->get_payload()) { // plus the size of the data
        calc_total_length += this->get_payload()->header_payload_to_array().size();
    }
    assert(calc_total_length <= (1<<16)-1); // should not be bigger than 2^16-1 (this cannot be stored in 2 octets)

    this->total_length = BitOperations::int16_to_char_arr(calc_total_length);
}

void IPv4Packet::set_identification(uint16_t prev_id) {
    this->identification = BitOperations::int16_to_char_arr(prev_id);
}

void IPv4Packet::set_df_flag(bool b) {
    this->flags_fragment_offset[0] = BitOperations::set_nth_lsb(this->flags_fragment_offset[0], 6, b); // set 2nd msb to 1 or 0 (depending on b)
}

void IPv4Packet::set_mf_flag(bool b) {
    this->flags_fragment_offset[0] = BitOperations::set_nth_lsb(this->flags_fragment_offset[0], 5, b);
}

void IPv4Packet::set_fragment_offset(uint16_t offset) {
    if (offset > (1<<13)-1) { // i.e. offset > 2^13-1 => more than 13 bits present
        throw std::invalid_argument("Offset must be between 0 and 8191");
    }
    // set 5 lower bits to value of 8 upper bits of offset
    this->flags_fragment_offset[0] = (unsigned char) BitOperations::set_n_lower_bits(flags_fragment_offset[0], offset >> 8, 5);
    this->flags_fragment_offset[1] = (unsigned char) offset;
}

void IPv4Packet::set_time_to_live(unsigned char time_to_live) {
    this->time_to_live = time_to_live;
}

void IPv4Packet::set_protocol(unsigned char protocol) {
    this->protocol = protocol;
}

void IPv4Packet::set_header_checksum() {
    std::vector<unsigned char> header_arr = header_to_array();
    unsigned int count = header_arr.size();
    assert(count % 2 == 0); // it should be a multiple of 16 bytes
    unsigned long int sum = 0;
    unsigned int addr = 0;
    while( count > 1 )  {
        unsigned short val16bit = ((unsigned short) header_arr[addr])<<8 + header_arr[++addr];
        /*  This is the inner loop */
        sum += val16bit;
        addr++;
        count -= 2;
    }

    /*  Fold 32-bit sum to 16 bits */
    while (sum>>16)
        sum = (sum & 0xffff) + (sum >> 16);

    sum = ~sum;
    
    this->header_checksum = {
        (unsigned char) (sum >> 8),
        (unsigned char) sum
    };
}

void IPv4Packet::set_options(std::vector<unsigned char> options) {
    this->options = options;
    if (options.size() % 4 != 0) { // if our options are not a multiple of 32-bits / 4 octets
        this->options.push_back(0); // add the end of options marker
    }
}

void IPv4Packet::set_padding() {
    unsigned char rest = this->options.size() % 4;
    for (unsigned char i = 0; i < rest; i++) {
        this->padding.push_back(0); // add padding until a multiple of 32 bits
    }
    assert(this->header_to_array().size() % 4 == 0); // the header should be a multiple of 32 bits after adding padding
}

unsigned char IPv4Packet::get_dscp() {
    return BitOperations::read_n_upper_bits(this->dscp_ecn, 6);
}

unsigned char IPv4Packet::get_ecn() {
    return BitOperations::read_n_lower_bits(this->dscp_ecn, 2);
}

std::vector<unsigned char> IPv4Packet::header_to_array() {
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
    std::for_each(this->options.begin(), this->options.end(), add_to_header);
    std::for_each(this->padding.begin(), this->padding.end(), add_to_header);
    return header;
}

std::vector<unsigned char> IPv4Packet::header_payload_to_array() {
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

void IPv4Packet::recalculate_fields() {
    set_padding();
    set_ihl();
    set_total_length();
    set_header_checksum();
}