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
    virtual void set_fragment_offset(int offset) = 0;
    virtual void set_time_to_live(unsigned char time_to_live) = 0;
    virtual void set_protocol(ProtocolTypeInterface *p) = 0;
    virtual void set_header_checksum() = 0;
    virtual void set_source(IPv4AddressInterface *address) = 0;
    virtual void set_destination(IPv4AddressInterface *address) = 0;
};

#endif /* IPV4PACKETINTERFACE_H_ */
