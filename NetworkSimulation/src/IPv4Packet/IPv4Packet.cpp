#include "IPv4Packet.h"
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include "../BitOperations/BitOperations.h"
#include "../ProtocolUtils/ProtocolUtils.h"
#include "../ProtocolConstants/ProtocolConstants.h"

const unsigned char IPv4Packet::default_header_size = 20; // IHL w/o options+padding (in octets, not in 32-bit blocks as IHL is measured in)
const unsigned char IPv4Packet::ip_version = 4;
void IPv4Packet::set_version() {
    // set upper 4 bits to wanted version
    this->ip_header[0] = BitOperations::set_n_upper_bits(this->ip_header[0], ip_version, 4);
}

unsigned char IPv4Packet::get_version() {
    return BitOperations::read_n_upper_bits(this->ip_header[0], 4);
}

void IPv4Packet::set_ihl() {
    int octet_amount = this->ip_header.size() + this->options.size();
    assert(octet_amount % 4 == 0); // header should ALWAYS be a multiple 32 bits / 4 octets - if not, something is wrong
    // set 4 lower bits to the amount of 4-octet / 32bit values
    this->ip_header[0] = BitOperations::set_n_lower_bits(this->ip_header[0], octet_amount/4, 4);
}

unsigned char IPv4Packet::get_ihl() {
    return BitOperations::read_n_lower_bits(this->ip_header[0], 4);
}

void IPv4Packet::set_dscp(unsigned char dscp) {
    if (dscp > IPv4Constants::BoundaryConstants::DSCP_MAX) { // dscp values are between 0-63
        throw std::invalid_argument("DSCP values must be between 0-63");
    }
    assert(dscp <= IPv4Constants::BoundaryConstants::DSCP_MAX);

    // set 6 upper bits to dscp
    this->ip_header[1] = BitOperations::set_n_upper_bits(this->ip_header[1], dscp, 6);
}

unsigned char IPv4Packet::get_dscp() {
    return BitOperations::read_n_upper_bits(this->ip_header[1], 6);
}

void IPv4Packet::set_ecn(unsigned char ecn) {
    if (ecn > IPv4Constants::BoundaryConstants::ECN_MAX) { // ecn values are between 0-3
        throw std::invalid_argument("ECN values must be between 0-3");
    }
    assert(ecn <= IPv4Constants::BoundaryConstants::ECN_MAX);

    // set 2 lower bits to ecn
    this->ip_header[1] = BitOperations::set_n_lower_bits(this->ip_header[1], ecn, 2);
    assert(BitOperations::read_n_lower_bits(this->ip_header[1], 2) == ecn); // reading the two lower bits should give ecn
}

unsigned char IPv4Packet::get_ecn() {
    return BitOperations::read_n_lower_bits(this->ip_header[1], 2);
}

void IPv4Packet::set_total_length() {
    // it is at least the header size
    int calc_total_length = this->default_header_size + this->options.size();
    if (this->get_payload()) { // plus the size of the data
        calc_total_length += this->get_payload()->header_payload_to_array().size();
    }
    assert(calc_total_length <= IPv4Constants::BoundaryConstants::TOTAL_LENGTH_MAX); // should not be bigger than 2^16-1 (this cannot be stored in 2 octets)

    std::array<unsigned char, 2> total_length = BitOperations::int16_to_char_arr(calc_total_length);

    ip_header[2] = total_length[0];
    ip_header[3] = total_length[1];
}

uint16_t IPv4Packet::get_total_length() {
    return BitOperations::char_vector_to_int16({ip_header[2], ip_header[3]}, 0);
}

void IPv4Packet::set_identification(uint16_t prev_id) {
    std::array<unsigned char, 2> identification = BitOperations::int16_to_char_arr(prev_id);

    this->ip_header[4] = identification[0];
    this->ip_header[5] = identification[1];
}

uint16_t IPv4Packet::get_identification() {
    return BitOperations::char_vector_to_int16({ip_header[4], ip_header[5]}, 0);
}

void IPv4Packet::set_df_flag(bool b) {
    this->ip_header[6] = BitOperations::set_nth_lsb(this->ip_header[6], 6, b); // set 2nd msb to 1 or 0 (depending on b)
}

bool IPv4Packet::get_df_flag() {
    return BitOperations::read_nth_lsb(this->ip_header[6], 6);
}

void IPv4Packet::set_mf_flag(bool b) {
    this->ip_header[6] = BitOperations::set_nth_lsb(this->ip_header[6], 5, b);
}

bool IPv4Packet::get_mf_flag() {
    return BitOperations::read_nth_lsb(this->ip_header[6], 5);
}

void IPv4Packet::set_fragment_offset(uint16_t offset) {
    if (offset > IPv4Constants::BoundaryConstants::FRAGMENT_OFFSET_MAX) { // i.e. offset > 2^13-1 => more than 13 bits present
        throw std::invalid_argument("Offset must be between 0 and 8191");
    }
    // set 5 lower bits to value of 8 upper bits of offset
    this->ip_header[6] = (unsigned char) BitOperations::set_n_lower_bits(ip_header[6], offset >> 8, 5);
    this->ip_header[7]  = (unsigned char) offset;
}

uint16_t IPv4Packet::get_fragment_offset() {
    uint16_t fragment_offset = BitOperations::char_arr_to_int16({BitOperations::read_n_lower_bits(this->ip_header[6], 5), this->ip_header[7]});
    
    if (fragment_offset > IPv4Constants::BoundaryConstants::FRAGMENT_OFFSET_MAX) {
        throw std::invalid_argument("Offset must be between 0 and 8191");
    }

    return fragment_offset;
}

void IPv4Packet::set_time_to_live(unsigned char time_to_live) {
    this->ip_header[8] = time_to_live;
}

unsigned char IPv4Packet::get_time_to_live() {
    return this->ip_header[8];
}

void IPv4Packet::set_protocol(unsigned char protocol) {
    this->ip_header[9] = protocol;
}

unsigned char IPv4Packet::get_protocol() {
    return this->ip_header[9];
}

void IPv4Packet::set_header_checksum() {
    this->ip_header[10] = 0; // make sure the checksum is 0 before we calculate the checksum over the entire header
    this->ip_header[11] = 0; // otherwise an old checksum may be included in the calculation (!!)

    std::vector<unsigned char> header_arr = header_to_array();
    std::array<unsigned char, 2> checksum = BitOperations::int16_to_char_arr(ProtocolUtils::calculate_internet_checksum(header_arr));
    this->ip_header[10] = checksum[0];
    this->ip_header[11] = checksum[1];
}

uint16_t IPv4Packet::get_header_checksum() {
    return BitOperations::char_arr_to_int16({ip_header[10], ip_header[11]});
}

void IPv4Packet::set_source(std::vector<unsigned char> source) {
    if (source.size() != 4) {
        throw std::invalid_argument("Source address must be of length 4");
    }
    this->ip_header[12] = source[0];
    this->ip_header[13] = source[1];
    this->ip_header[14] = source[2];
    this->ip_header[15] = source[3];
}

std::vector<unsigned char> IPv4Packet::get_source() {
    return {this->ip_header[12], this->ip_header[13], this->ip_header[14], this->ip_header[15]};
}

void IPv4Packet::set_destination(std::vector<unsigned char> destination) {
    if (destination.size() != 4) {
        throw std::invalid_argument("Source address must be of length 4");
    }
    this->ip_header[16] = destination[0];
    this->ip_header[17] = destination[1];
    this->ip_header[18] = destination[2];
    this->ip_header[19] = destination[3];
}

std::vector<unsigned char> IPv4Packet::get_destination() {
    return {this->ip_header[16], this->ip_header[17], this->ip_header[18], this->ip_header[19]};
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
        this->options.push_back(0); // add padding until a multiple of 32 bits
    }
    assert(this->header_to_array().size() % 4 == 0); // the header should be a multiple of 32 bits after adding padding
}



std::vector<unsigned char> IPv4Packet::header_to_array() {
    std::vector<unsigned char> ip_header_with_options = ip_header;
    for (unsigned char c : options) {ip_header_with_options.push_back(c);}
    return ip_header_with_options;
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