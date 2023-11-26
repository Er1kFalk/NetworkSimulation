/*
 * IPv4Packet.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include "IPv4PacketInterface.h"
#include <stdint.h>
#include <cassert>

#ifndef IPV4PACKET_H_
#define IPV4PACKET_H_

class IPv4Packet : public IPv4PacketInterface {
private:

    std::vector<unsigned char> ip_header;
    std::vector<unsigned char> options;
    std::shared_ptr<CommunicationProtocol> payload;

    static const unsigned char default_header_size;
    static const unsigned char ip_version;
public:
    IPv4Packet() {
        this->ip_header.resize(20); // default header size
        for (unsigned char& c : ip_header) {
            c = 0;
        }
        
        for (const unsigned char c : ip_header) {
            assert(c == 0);
        }
    }
    std::vector<unsigned char> header_to_array() override;

    unsigned char get_version() override;
    unsigned char get_ihl() override;
    unsigned char get_dscp() override;
    unsigned char get_ecn() override;
    uint16_t get_total_length() override;
    uint16_t get_identification() override;
    bool get_df_flag() override;
    bool get_mf_flag() override;
    uint16_t get_fragment_offset() override;
    unsigned char get_time_to_live() override;
    unsigned char get_protocol() override;
    uint16_t get_header_checksum() override;
    std::vector<unsigned char> get_source() override;
    std::vector<unsigned char> get_destination() override;
    std::vector<unsigned char> get_options() {return this->options;}

    void set_version() override;
    void set_ihl() override;
    void set_total_length() override;
    void set_header_checksum() override;
    void set_padding() override;

    void set_dscp(unsigned char dscp) override;
    void set_ecn(unsigned char ecn) override;
    void set_identification(uint16_t prev_id) override;
    void set_df_flag(bool b) override;
    void set_mf_flag(bool b) override;
    void set_fragment_offset(uint16_t offset) override;
    void set_time_to_live(unsigned char time_to_live) override;
    void set_protocol(unsigned char protocol) override;
    void set_source(std::vector<unsigned char> source) override;
    void set_destination(std::vector<unsigned char> destination) override;
    void set_options(std::vector<unsigned char> options) override;

    void set_payload(std::shared_ptr<CommunicationProtocol> payload) override {
        this->payload = payload;
        set_ihl();
        set_total_length();
        set_header_checksum();
    }
    std::shared_ptr<CommunicationProtocol> get_payload() override {return this->payload;}

    std::vector<unsigned char> header_payload_to_array() override;

    void recalculate_fields() override;

    std::shared_ptr<IPv4PacketInterface> copy() {return std::make_shared<IPv4Packet>(*this);}

    // IPv4Packet(unsigned char dscp, unsigned char ecn, uint16_t identification_id, bool df, bool mf, uint16_t offset, unsigned char time_to_live, unsigned char p, std::array<unsigned char, 4> source, std::array<unsigned char, 4> destination, std::vector<unsigned char> options, std::shared_ptr<CommunicationProtocol> payload) {
    //     set_version();
    //     set_dscp(dscp);
    //     set_ecn(ecn);
    //     set_identification(identification_id);
    //     set_df_flag(df);
    //     set_mf_flag(mf);
    //     set_fragment_offset(offset);
    //     set_time_to_live(time_to_live);
    //     set_protocol(p);
        
    //     set_source(source);
    //     set_destination(destination);
    //     set_options(options);
    //     this->payload = payload;
    //     set_padding();
    //     set_ihl();
    //     set_total_length();
    //     set_header_checksum();
    // }
};



#endif /* IPV4PACKET_H_ */
