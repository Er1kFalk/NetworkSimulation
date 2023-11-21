#ifndef TCPEVENT_H_
#define TCPEVENT_H_

#include <tuple>
#include <memory>
#include <map>

#include "../../TCPSegment/TCPSegmentInterface.h"
#include "../../TCPSegment/TCPSegment.h"
#include "../BaseScheduler/Event.h"

#include "TCPSimulatorTypeDefs.h"
#include "../NetworkNodeSimulator/SimulatorTypeDefs.h"
#include "../BaseScheduler/EventTypeDefs.h"

class TCPState {
private:
    std::shared_ptr<TCPSegmentInterface> current_segment;
    bool is_retransmission; // true if this segment is a retransmission of a previous one
    bool first_rtt_measurement_made; // true if we have measured the first RTT in this session, otherwise false 
    int SRTT, RTTVAR, RTO;
public:
    TCPState(std::shared_ptr<TCPSegmentInterface> current_segment) {
        this->current_segment = current_segment;
        this->SRTT = 0;
        this->RTTVAR = 0;
        this->RTO = 3000; // initially set to 3 seconds (3000ms)
        this->is_retransmission = false;
        this->first_rtt_measurement_made = false;
    }

    int get_srtt() {return this->SRTT;}
    int get_rttvar() {return this->RTTVAR;}
    int get_rto() {return this->RTO;}
    std::shared_ptr<TCPSegmentInterface> get_current_segment() {return this->current_segment;}
    bool get_is_retransmission() {return this->is_retransmission;}
    bool get_first_rtt_measurement_made() {return this->first_rtt_measurement_made;}

    void set_srtt(int SRTT) {this->SRTT = SRTT;}
    void set_rttvar(int RTTVAR) {this->RTTVAR = RTTVAR;}
    void set_rto(int RTO) {this->RTO = RTO;}
    void set_current_segment(std::shared_ptr<TCPSegmentInterface> current_segment) {this->current_segment = current_segment;}
    void set_is_retransmission(bool is_retransmission) {this->is_retransmission = is_retransmission;}
    void set_first_rtt_measurement_made(bool first_rtt_measurement_made) {this->first_rtt_measurement_made = first_rtt_measurement_made;}

    std::shared_ptr<TCPState> copy() {return std::make_shared<TCPState>(*this);}
};

class TCPEvent : public Event, public std::enable_shared_from_this<TCPEvent> {
protected: 
    // <enum class SV {INIT_CONN, SYN_SENT, LOSS_DETECTION, AWAIT_SYN_ACK, SYN_ACK_RECEIVED, ACK_SENT, ESTABLISHED};
    // SV current_state;>
    std::vector<TCPEventRulePtr> event_rules;
    std::shared_ptr<TCPState> current_client_state;
    std::shared_ptr<TCPState> current_server_state;
    NetworkLayer nlayer; // network protocol to pass TCP data to
    static std::map<std::tuple<NetworkLayer, Transmitter>, TCPEventRulePtr> pass_to_layer;
public:
    TCPEvent(std::shared_ptr<TCPState> current_client_state, std::shared_ptr<TCPState> current_server_state, NetworkLayer nlayer) {
        this->current_client_state = current_client_state;
        this->current_server_state = current_server_state;
        this->nlayer = nlayer;
        this->set_transmitter(Transmitter::Client);

        // this->current_client_state->set_source_port(client_source_port);
        // this->current_client_state->set_destination_port(client_destination_port);
	    // this->current_client_state->set_sequence_nr(231321); // random
        // this->current_client_state->set_window_size(65465);

        // this->current_server_state->set_source_port(client_destination_port);
	    // this->current_server_state->set_destination_port(client_source_port);
	    // this->current_server_state->set_sequence_nr(231321); // random
        // this->current_server_state->set_window_size(65465);
    }

    void set_current_client_state(std::shared_ptr<TCPState> current_client_state) {this->current_client_state = current_client_state;}
    void set_current_server_state(std::shared_ptr<TCPState> current_server_state) {this->current_server_state = current_server_state;}
    
    std::shared_ptr<TCPState> get_current_client_state() {return current_client_state;}
    std::shared_ptr<TCPState> get_current_server_state() {return current_server_state;}
    
    void set_event_rules(std::vector<TCPEventRulePtr> event_rules)  {this->event_rules = event_rules;}
    std::vector<TCPEventRulePtr> get_event_rules() {return this->event_rules;}
    
    void set_nlayer(NetworkLayer nlayer) {this->nlayer = nlayer;}
    NetworkLayer get_nlayer() {return nlayer;}
    
    std::shared_ptr<TCPEvent> copy() { // copy the state. but reset everything else
        std::shared_ptr<TCPEvent> e = std::make_shared<TCPEvent>(*this);
        e->current_client_state = this->current_client_state->copy();
        e->current_server_state = this->current_server_state->copy();
        e->event_rules = {};
        return e;
    }

    void apply_rules(std::shared_ptr<BaseScheduler> scheduler) override;
};

#endif