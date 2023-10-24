/*
 * IPv4Packet.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include "IPv4PacketInterface.h"

#ifndef IPV4PACKET_H_
#define IPV4PACKET_H_

class IPv4Packet : public IPv4PacketInterface {
private:
    unsigned char version_ihl;
    std::shared_ptr<TrafficClassInterface> type_of_service;
    std::array<unsigned char, 2> total_length;
    std::array<unsigned char, 2> identification;
    unsigned char flags;
    std::array<unsigned char, 3> fragment_offset;
    unsigned char time_to_live;
    std::shared_ptr<ProtocolTypeInterface> protocol;
    std::array<unsigned char, 2> header_checksum;
    std::shared_ptr<IPv4AddressInterface> source;
    std::shared_ptr<IPv4AddressInterface> destination;
public:
    void set_version() override;
    void set_ihl() override;
    void set_type_of_service(std::shared_ptr<TrafficClassInterface> t) override;
    void set_total_length() override;
    void set_identification(int prev_id) override;
    void set_df_flag(bool b) override;
    void set_mf_flag(bool b) override;
    void set_fragment_offset(unsigned int offset) override;
    void set_time_to_live(unsigned char time_to_live) override;
    void set_protocol(std::shared_ptr<ProtocolTypeInterface> p) override;
    void set_header_checksum() override;
    void set_source(std::shared_ptr<IPv4AddressInterface> address) override;
    void set_destination(std::shared_ptr<IPv4AddressInterface> address) override;
    std::vector<unsigned char> to_array() override;

    unsigned char get_version() override {return this->version_ihl>>4;}
    unsigned char get_ihl() override {return 0b1111 & this->version_ihl;}
    std::shared_ptr<TrafficClassInterface>  get_type_of_service() override {return this->type_of_service;}
    std::array<unsigned char, 2> get_total_length() override {return this->total_length;}
    std::array<unsigned char, 2> get_identification() override {return this->identification;}
    unsigned char get_df_flag() override {return 0b10 & this->flags;}
    unsigned char get_mf_flag() override {return 0b100 & this->flags;}
    std::array<unsigned char, 3> get_fragment_offset() override {return this->fragment_offset;}
    std::array<unsigned char, 3> get_flags_fragment_offset() override;
    unsigned char get_time_to_live() override {return this->time_to_live;}
    std::shared_ptr<ProtocolTypeInterface> get_protocol() override {return this->protocol;}
    std::array<unsigned char, 2> get_header_checksum() override {return this->header_checksum;}
    std::shared_ptr<IPv4AddressInterface> get_source() override {return this->source;}
    std::shared_ptr<IPv4AddressInterface> get_destination() override {return this->destination;}

    IPv4Packet(std::shared_ptr<TrafficClassInterface> t, int identification_id, bool df, bool mf, unsigned int offset, unsigned char time_to_live, std::shared_ptr<ProtocolTypeInterface> p, std::shared_ptr<IPv4AddressInterface> source, std::shared_ptr<IPv4AddressInterface> destination, std::shared_ptr<CommunicationProtocol> payload) {
        set_version();
        set_ihl();
        set_type_of_service(t);
        set_total_length();
        set_identification(identification_id);
        set_df_flag(df);
        set_mf_flag(mf);
        set_fragment_offset(offset);
        set_time_to_live(time_to_live);
        set_protocol(p);
        set_header_checksum();
        set_source(source);
        set_destination(destination);
        set_payload(payload);
    }
};

#endif /* IPV4PACKET_H_ */
