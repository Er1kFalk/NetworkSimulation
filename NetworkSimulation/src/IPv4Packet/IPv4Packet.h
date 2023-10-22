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
    unsigned char version : 4;
    unsigned char ihl : 4;
    TrafficClassInterface *type_of_service;
    std::vector<unsigned char> total_length;
    std::vector<unsigned char> identification;
    unsigned char df_flag : 1;
    unsigned char mf_flag : 1;
    std::vector<unsigned char> offset;
    unsigned char time_to_live;
    ProtocolTypeInterface *protocol;
    std::vector<unsigned char> header_checksum;
    IPv4AddressInterface *source;
    IPv4AddressInterface *destination;
public:
    void set_version() override;
    void set_ihl() override;
    void set_type_of_service(TrafficClassInterface *t) override;
    void set_total_length() override;
    void set_identification(int prev_id) override;
    void set_df_flag(bool b) override;
    void set_mf_flag(bool b) override;
    void set_fragment_offset(int offset) override;
    void set_time_to_live(unsigned char time_to_live) override;
    void set_protocol(ProtocolTypeInterface *p) override;
    void set_header_checksum() override;
    void set_source(IPv4AddressInterface *address) override;
    void set_destination(IPv4AddressInterface *address) override;
    std::vector<unsigned char> to_array() override;
};

#endif /* IPV4PACKET_H_ */
