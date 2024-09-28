#include "TCPSegment.h"
#include "../../UtilityLibraries/BitOperations/BitOperations.h"
#include "../../UtilityLibraries/ProtocolUtils/ProtocolUtils.h"
#include <stdexcept>

void TCPSegment::set_ipv4_pseudo_header(std::vector<unsigned char> source_ip_address, std::vector<unsigned char> destination_ip_address) {
    if (source_ip_address.size() != 4) {
        throw std::invalid_argument("source_ip_address must be of size 4");
    } else if (destination_ip_address.size() != 4) {
        throw std::invalid_argument("destination_ip_address must be of size 4");
    }
    assert(source_ip_address.size() == 4 && destination_ip_address.size() == 4);

    this->ipv4_pseudo_header = {};
    for (unsigned char c : source_ip_address) {ipv4_pseudo_header.push_back(c);}
    for (unsigned char c : destination_ip_address) {ipv4_pseudo_header.push_back(c);}
    ipv4_pseudo_header.push_back(0);
    ipv4_pseudo_header.push_back(0x06);
    
    std::vector<unsigned char> tcplength = BitOperations::int16_into_char_vector(header_payload_to_array().size(), {0,0}, 0);
    for (unsigned char c : tcplength) {ipv4_pseudo_header.push_back(c);}
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

void TCPSegment::set_acknowledgement_nr(uint32_t ack) {
    // sets elements 8-11 to ack value
    this->tcp_header = BitOperations::int32_into_char_vector(ack, this->tcp_header, 8);
}

void TCPSegment::set_data_offset() {
    assert(options.size() % 4 == 0);
    const unsigned char header_length = 5 + options.size()/4;

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
    this->tcp_header = BitOperations::int16_into_char_vector(0, this->tcp_header, 16); // reset checksum - otherwise old checksums will be included in calculation!
    if (this->ipv4_pseudo_header.size() != 12) {
        throw std::invalid_argument("cannot calculate checksum when ipv4 pseudo header not set");
    }

    // calculate checksum over tcp pseudo header + header + data
    std::vector<unsigned char> data_to_calculate_checksum_over = ipv4_pseudo_header;
    std::vector<unsigned char> tcp_segment = header_payload_to_array();
    for (unsigned char c : tcp_segment) {data_to_calculate_checksum_over.push_back(c);}

    if (data_to_calculate_checksum_over.size() % 2 != 0) { // pad it with 0 if uneven (since checksum is calculated over 16-bit chunks)
        data_to_calculate_checksum_over.push_back(0);
    }
    assert(data_to_calculate_checksum_over.size() % 2 == 0);


    this->tcp_header = BitOperations::int16_into_char_vector(ProtocolUtils::calculate_internet_checksum(data_to_calculate_checksum_over), this->tcp_header, 16);
}

void TCPSegment::set_urgent_pointer(uint16_t urgent_pointer) {
    // set index 18-19 to urgent pointer
    this->tcp_header = BitOperations::int16_into_char_vector(urgent_pointer, this->tcp_header, 18);

}

void TCPSegment::set_options(std::vector <unsigned char> options) {
    this->options = options;
}

void TCPSegment::add_mss_option(uint16_t mss) {
    options.push_back(2); // mss option type
    options.push_back(4); // mss length
    std::array<unsigned char, 2> mss_arr = BitOperations::int16_to_char_arr(mss);
    options.push_back(mss_arr[0]);
    options.push_back(mss_arr[1]);
}

void TCPSegment::add_end_of_optionlist_option() {
    options.push_back(0);
}

void TCPSegment::add_no_operation_option() {
    options.push_back(1);
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

uint32_t TCPSegment::get_acknowledgement_nr() {
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

std::vector<unsigned char> TCPSegment::header_to_array() {
    std::vector<unsigned char> fullheader = this->tcp_header;

    for (unsigned char c : options) {
        fullheader.push_back(c);
    }

    return fullheader;
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

void TCPSegment::add_options_padding() {
    while (options.size() % 4 != 0) {
        add_no_operation_option();
    }
}

void TCPSegment::recalculate_fields() {
    add_options_padding();
    set_data_offset();
    uint32_t pseudo_header_length = header_payload_to_array().size();
    assert(pseudo_header_length <= UINT16_MAX); // if not we have overflow
    this->ipv4_pseudo_header = BitOperations::int16_into_char_vector(pseudo_header_length, this->ipv4_pseudo_header, 10);

    set_checksum();
}
