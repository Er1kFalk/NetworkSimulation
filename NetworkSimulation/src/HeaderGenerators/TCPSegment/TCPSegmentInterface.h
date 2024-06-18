/*
 * TCPSegmentInterface.h
 *
 *  Created on: 31 Oct 2023
 *      Author: erik
 */

#include "../CommunicationProtocol/CommunicationProtocol.h"
#include <stdint.h>

#ifndef TCPSEGMENTINTERFACE_H_
#define TCPSEGMENTINTERFACE_H_

class TCPSegmentInterface : public CommunicationProtocol {
private:

public:
    virtual void set_ipv4_pseudo_header(std::vector<unsigned char> source_address, std::vector<unsigned char> destination_address) = 0;

    /*Setters*/
    virtual void set_source_port(uint16_t port) = 0;
    virtual void set_destination_port(uint16_t port) = 0;
    virtual void set_sequence_nr(uint32_t seq) = 0;
    virtual void set_acknowledgement_nr(uint32_t seq) = 0;
    virtual void set_data_offset() = 0;

    virtual void set_cwr_flag(bool b) = 0;
    virtual void set_ece_flag(bool b) = 0;
    virtual void set_urg_flag(bool b) = 0;
    virtual void set_ack_flag(bool b) = 0;
    virtual void set_psh_flag(bool b) = 0;
    virtual void set_rst_flag(bool b) = 0;
    virtual void set_syn_flag(bool b) = 0;
    virtual void set_fin_flag(bool b) = 0;

    virtual void set_window_size(uint16_t wsize) = 0;
    virtual void set_checksum() = 0;
    virtual void set_urgent_pointer(uint16_t urgent_pointer) = 0;

    virtual void set_options(std::vector <unsigned char> options) = 0;
    virtual void add_mss_option(uint16_t mss) = 0;
    virtual void add_end_of_optionlist_option() = 0;
    virtual void add_no_operation_option() = 0;

    /*Getters*/
    virtual uint16_t get_source_port() = 0;
    virtual uint16_t get_destination_port() = 0;
    virtual uint32_t get_sequence_nr() = 0;
    virtual uint32_t get_acknowledgement_nr() = 0;
    virtual unsigned char get_data_offset() = 0;

    virtual bool get_cwr_flag() = 0;
    virtual bool get_ece_flag() = 0;
    virtual bool get_urg_flag() = 0;
    virtual bool get_ack_flag() = 0;
    virtual bool get_psh_flag() = 0;
    virtual bool get_rst_flag() = 0;
    virtual bool get_syn_flag() = 0;
    virtual bool get_fin_flag() = 0;

    virtual uint16_t get_window_size() = 0;
    virtual uint16_t get_checksum() = 0;
    virtual uint16_t get_urgent_pointer() = 0;

    virtual std::vector<unsigned char> get_ipv4_pseudo_header() = 0;

    virtual std::shared_ptr<TCPSegmentInterface> copy() = 0;
};

#endif /* TCPSEGMENTINTERFACE_H_ */
