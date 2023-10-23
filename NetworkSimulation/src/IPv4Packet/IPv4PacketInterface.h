/*
 * IPv4PacketInterface.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include "../TrafficClass/TrafficClassInterface.h"
#include "../ProtocolType/ProtocolTypeInterface.h"
#include "../IPv4Address/IPv4AddressInterface.h"
#include "../CommunicationProtocol.h"
#include <array>

#ifndef IPV4PACKETINTERFACE_H_
#define IPV4PACKETINTERFACE_H_

class IPv4PacketInterface : public CommunicationProtocol {
public:
    virtual void set_version() = 0;
    virtual void set_ihl() = 0;
    virtual void set_type_of_service(TrafficClassInterface *t) = 0;
    virtual void set_total_length() = 0;
    virtual void set_identification(int prev_id) = 0;
    virtual void set_df_flag(bool b) = 0;
    virtual void set_mf_flag(bool b) = 0;
    virtual void set_fragment_offset(unsigned int offset) = 0;
    virtual void set_time_to_live(unsigned char time_to_live) = 0;
    virtual void set_protocol(ProtocolTypeInterface *p) = 0;
    virtual void set_header_checksum() = 0;
    virtual void set_source(IPv4AddressInterface *address) = 0;
    virtual void set_destination(IPv4AddressInterface *address) = 0;

    virtual unsigned char get_version() = 0;
    virtual unsigned char get_ihl() = 0;
    virtual TrafficClassInterface* get_type_of_service() = 0;
    virtual std::array<unsigned char, 2> get_total_length() = 0;
    virtual std::array<unsigned char, 2> get_identification() = 0;
    virtual unsigned char get_df_flag() = 0;
    virtual unsigned char get_mf_flag() = 0;
    virtual std::array<unsigned char, 3> get_fragment_offset() = 0;
    virtual std::array<unsigned char, 3> get_flags_fragment_offset() = 0;
    virtual unsigned char get_time_to_live() = 0;
    virtual ProtocolTypeInterface* get_protocol() = 0;
    virtual std::array<unsigned char, 2> get_header_checksum() = 0;
    virtual IPv4AddressInterface* get_source() = 0;
    virtual IPv4AddressInterface* get_destination() = 0;
};

#endif /* IPV4PACKETINTERFACE_H_ */
