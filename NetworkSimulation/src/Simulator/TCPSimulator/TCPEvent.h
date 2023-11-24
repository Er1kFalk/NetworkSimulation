#ifndef TCPEVENT_H_
#define TCPEVENT_H_

#include <tuple>
#include <memory>
#include <map>
#include <queue>

#include "../../TCPSegment/TCPSegmentInterface.h"
#include "../../TCPSegment/TCPSegment.h"
#include "../BaseScheduler/Event.h"

#include "TCPSimulatorTypeDefs.h"
#include "../NetworkNodeSimulator/SimulatorTypeDefs.h"
#include "../BaseScheduler/EventTypeDefs.h"

#include <iostream>

class TCPState {
private:
    std::shared_ptr<TCPSegmentInterface> current_segment;
    std::shared_ptr<std::queue<std::vector<unsigned char>>> data_send_queue;
    std::shared_ptr<std::queue<uint32_t>> interpacket_delays;
    uint32_t initial_seq_nr;
    uint32_t bytes_sent;
    uint32_t bytes_received;
public:
    TCPState(std::shared_ptr<TCPSegmentInterface> current_segment) {
        this->current_segment = current_segment;
        this->initial_seq_nr = 0;
        this->bytes_sent = 0;
        this->bytes_received = 0;
        this->data_send_queue = std::make_shared<std::queue<std::vector<unsigned char>>>();
        this->interpacket_delays = std::make_shared<std::queue<uint32_t>>();
    }

    std::shared_ptr<TCPSegmentInterface> get_current_segment() {return this->current_segment;}

    void set_current_segment(std::shared_ptr<TCPSegmentInterface> current_segment) {this->current_segment = current_segment;}
    void add_to_data_send_queue(std::vector<unsigned char> packet) {data_send_queue->push(packet);}
    void remove_from_data_send_queue() {data_send_queue->pop();}
    std::vector<unsigned char> data_send_queue_see_first() {return data_send_queue->front();}
    bool data_send_queue_empty() {return data_send_queue->empty();}

    void add_bytes_received(uint32_t bytes_received) {this->bytes_received+=bytes_received;}
    uint32_t get_bytes_received() {return this->bytes_received;}
    
    void add_bytes_sent(uint32_t bytes_sent) {this->bytes_sent+=bytes_sent;}
    uint32_t get_bytes_sent() {return this->bytes_sent;}

    uint32_t get_initial_seq_nr() {return this->initial_seq_nr;}

    void set_initial_seqnr(uint32_t initial_seq_nr) {this->initial_seq_nr = initial_seq_nr;}

    void add_to_interpacket_delays(uint32_t delay) {this->interpacket_delays->push(delay);}
    void remove_from_interpacket_delays() {this->interpacket_delays->pop();}
    uint32_t interpacket_delays_see_first() {return this->interpacket_delays->front();}
    bool interpacket_delays_send_queue_empty() {return this->interpacket_delays->empty();}

    std::shared_ptr<TCPState> copy() {
        auto newstate = std::make_shared<TCPState>(*this);
        newstate->current_segment = this->current_segment->copy();
        return newstate;
    }
};

class TCPEvent : public Event, public std::enable_shared_from_this<TCPEvent> {
protected: 
    // <enum class SV {INIT_CONN, SYN_SENT, LOSS_DETECTION, AWAIT_SYN_ACK, SYN_ACK_RECEIVED, ACK_SENT, ESTABLISHED};
    // SV current_state;>
    std::vector<TCPEventRulePtr> event_rules;
    std::shared_ptr<TCPState> current_client_state;
    std::shared_ptr<TCPState> current_server_state;
    std::shared_ptr<std::queue<GFStructs::TransmittingNow>> send_order;
    NetworkLayer nlayer; // network protocol to pass TCP data to
    static std::map<std::tuple<GFStructs::ProtocolModel, GFStructs::TransmittingNow>, TCPEventRulePtr> pass_to_layer;
public:
    TCPEvent(std::shared_ptr<TCPState> current_client_state, std::shared_ptr<TCPState> current_server_state, NetworkLayer nlayer) {
        this->current_client_state = current_client_state;
        this->current_server_state = current_server_state;
        this->nlayer = nlayer;
        this->set_transmitter(GFStructs::TransmittingNow::Client);
        this->send_order = std::make_shared<std::queue<GFStructs::TransmittingNow>>();
    }

    void set_current_client_state(std::shared_ptr<TCPState> current_client_state) {this->current_client_state = current_client_state;}
    void set_current_server_state(std::shared_ptr<TCPState> current_server_state) {this->current_server_state = current_server_state;}
    
    std::shared_ptr<TCPState> get_current_client_state() {return current_client_state;}
    std::shared_ptr<TCPState> get_current_server_state() {return current_server_state;}
    
    void set_event_rules(std::vector<TCPEventRulePtr> event_rules)  {this->event_rules = event_rules;}
    std::vector<TCPEventRulePtr> get_event_rules() {return this->event_rules;}
    
    void set_nlayer(NetworkLayer nlayer) {this->nlayer = nlayer;}
    NetworkLayer get_nlayer() {return nlayer;}

    void add_to_send_order(GFStructs::TransmittingNow sender) {this->send_order->push(sender);}
    void remove_from_send_order() {
        if (this->send_order->front() == GFStructs::TransmittingNow::Client) {
            std::cout << "removed client from send order" << std::endl;
        } else {
            std::cout << "removed server from send order" << std::endl;
        }
        this->send_order->pop();
    }
    GFStructs::TransmittingNow send_order_see_first() {return this->send_order->front();}
    bool send_queue_empty() {return this->send_order->empty();}

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