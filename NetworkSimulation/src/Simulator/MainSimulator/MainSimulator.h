#ifndef MAINSIMULATOR_H_
#define MAINSIMULATOR_H_

#include <variant>
#include <memory>
#include <vector>
#include <stdexcept>
#include <variant>
#include <memory>
#include <map>
#include <algorithm>
#include <limits>

class TCPScheduler;
class IPv4Scheduler;
class NetworkProperties;
class BaseScheduler;
class CommunicationProtocol;
class TCPState;
class EthernetFrameInterface;
class IPv4PacketInterface;
class Event;


typedef std::variant<std::shared_ptr<TCPScheduler>, std::shared_ptr<IPv4Scheduler>> Scheduler;

class MainSimulator : public std::enable_shared_from_this<MainSimulator> {
private:
    std::shared_ptr<NetworkProperties> np;
    std::vector<std::shared_ptr<BaseScheduler>> schedulers;
    std::shared_ptr<BaseScheduler> scheduler_tcp;
    std::shared_ptr<BaseScheduler> scheduler_ipv4;
    std::shared_ptr<BaseScheduler> scheduler_ethernet;
    uint64_t time;

    std::shared_ptr<BaseScheduler> get_next_scheduler();

public:
    MainSimulator(std::shared_ptr<NetworkProperties> np);

    void initialize();

    void run();

    /*
    receiver redirecting to pcap
    */

   void receive_message(std::vector<unsigned char> data, uint64_t time);

    /*
    receiver redirecting to ethernet
    */
    void receive_message(std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<EthernetFrameInterface> initial_protocol_state, uint64_t time);

    /*
    receiver redirecting to ipv4
    */
    void receive_message(std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<IPv4PacketInterface> initial_protocol_state, uint64_t time);

    /*
    receiver redirecting to tcp
    */
    void receive_message(std::shared_ptr<TCPState> client, std::shared_ptr<TCPState> server, uint64_t time);

    std::shared_ptr<NetworkProperties> get_np() {return np;}    
};
#endif