/*
 * IPv4Packet.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include "IPv4PacketInterface.h"
#include <stdint.h>

#ifndef IPV4PACKET_H_
#define IPV4PACKET_H_

class IPv4Packet : public IPv4PacketInterface {
private:
    unsigned char version_ihl;
    unsigned char dscp_ecn; // type of service
    std::array<unsigned char, 2> total_length;
    std::array<unsigned char, 2> identification;
    std::array<unsigned char, 2> flags_fragment_offset;
    unsigned char time_to_live;
    unsigned char protocol;
    std::array<unsigned char, 2> header_checksum;
    std::array<unsigned char, 4> source;
    std::array<unsigned char, 4> destination;
    std::vector<unsigned char> options;
    std::vector<unsigned char> padding;

    std::shared_ptr<CommunicationProtocol> payload;

    static const unsigned char default_header_size;
    static const unsigned char ip_version;
public:
    
    std::vector<unsigned char> header_to_array() override;

    unsigned char get_version() override {return this->version_ihl>>4;}
    unsigned char get_ihl() override {return 0b1111 & this->version_ihl;}
    unsigned char  get_dscp_ecn() override {return this->dscp_ecn;}
    unsigned char get_dscp() override;
    unsigned char get_ecn() override;
    std::array<unsigned char, 2> get_total_length() override {return this->total_length;}
    std::array<unsigned char, 2> get_identification() override {return this->identification;}
    std::array<unsigned char, 2> get_flags_fragment_offset() override {return this->flags_fragment_offset;}
    unsigned char get_time_to_live() override {return this->time_to_live;}
    unsigned char get_protocol() override {return this->protocol;}
    std::array<unsigned char, 2> get_header_checksum() override {return this->header_checksum;}
    std::array<unsigned char, 4> get_source() override {return this->source;}
    std::array<unsigned char, 4> get_destination() override {return this->destination;}
    std::vector<unsigned char> get_options() {return this->options;}
    std::vector<unsigned char> get_padding() {return this->padding;}

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
    void set_source(std::array<unsigned char, 4> source) {this->source = source;}
    void set_destination(std::array<unsigned char, 4> destination) {this->destination = destination;}
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
