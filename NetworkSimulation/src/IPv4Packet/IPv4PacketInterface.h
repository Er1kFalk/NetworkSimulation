/*
 * IPv4PacketInterface.h
 *
 *  Created on: 22 Oct 2023
 *      Author: erik
 */

#include "../CommunicationProtocol.h"
#include <array>
#include <memory>

#ifndef IPV4PACKETINTERFACE_H_
#define IPV4PACKETINTERFACE_H_

class IPv4PacketInterface : public CommunicationProtocol {
public:
    virtual void set_version() = 0;
    virtual void set_ihl() = 0;
    virtual void set_dscp(unsigned char dscp) = 0;
    virtual void set_ecn(unsigned char ecn) = 0;
    virtual void set_total_length() = 0;
    virtual void set_identification(int prev_id) = 0;
    virtual void set_df_flag(bool b) = 0;
    virtual void set_mf_flag(bool b) = 0;
    virtual void set_fragment_offset(unsigned int offset) = 0;
    virtual void set_time_to_live(unsigned char time_to_live) = 0;
    virtual void set_protocol(unsigned char protocol) = 0;
    virtual void set_header_checksum() = 0;
    virtual void set_source(std::array<unsigned char, 4> address) = 0;
    virtual void set_destination(std::array<unsigned char, 4> address) = 0;

    virtual unsigned char get_version() = 0;
    virtual unsigned char get_ihl() = 0;
    virtual unsigned char get_dscp_ecn() = 0;
    virtual unsigned char get_dscp() = 0;
    virtual unsigned char get_ecn() = 0;
    virtual std::array<unsigned char, 2> get_total_length() = 0;
    virtual std::array<unsigned char, 2> get_identification() = 0;
    virtual unsigned char get_df_flag() = 0;
    virtual unsigned char get_mf_flag() = 0;
    virtual std::array<unsigned char, 3> get_fragment_offset() = 0;
    virtual std::array<unsigned char, 3> get_flags_fragment_offset() = 0;
    virtual unsigned char get_time_to_live() = 0;
    virtual unsigned char get_protocol() = 0;
    virtual std::array<unsigned char, 2> get_header_checksum() = 0;
    virtual std::array<unsigned char, 4> get_source() = 0;
    virtual std::array<unsigned char, 4> get_destination() = 0;
};

#endif /* IPV4PACKETINTERFACE_H_ */
