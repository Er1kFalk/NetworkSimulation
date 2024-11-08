#ifndef NETWORKNODE_SIMULATOR_H_
#define NETWORKNODE_SIMULATOR_H_

#include <variant>
#include <memory>
#include <vector>
#include <stdexcept>
#include <variant>
#include <memory>
#include <map>
#include <algorithm>
#include <limits>

#include "../../ConfigReader/GeneratorFileConfigReader/GeneratorFileConfigReader.h"

class NetworkProperties;
class BaseScheduler;
class CommunicationProtocol;
class TCPState;
class EthernetFrameInterface;
class IPv4PacketInterface;
class Event;
class PCAPWriter;

class NetworkNodeSimulator : public std::enable_shared_from_this<NetworkNodeSimulator> {
private:
    std::shared_ptr<NetworkProperties> np;
    std::shared_ptr<BaseScheduler> scheduler;
    uint32_t time_sec; // seconds
    uint32_t time_us; // microseconds
    uint32_t max_gen_time; // seconds
    std::shared_ptr<PCAPWriter> pcapwriter;
    std::shared_ptr<GeneratorFileConfigReader> confreader;
    std::map<uint32_t, GFStructs::GeneratorFile> generatorfiles;

public:
    NetworkNodeSimulator(std::shared_ptr<NetworkProperties> np, std::shared_ptr<PCAPWriter> pcapwriter, std::shared_ptr<GeneratorFileConfigReader> confreader, uint32_t max_gen_time);

    void initialize_tcp_event(uint32_t id, GFStructs::GeneratorFile gf);
    void initialize_ipv4_event(uint32_t id, GFStructs::GeneratorFile gf);
    void initialize_ethernet_event(uint32_t id, GFStructs::GeneratorFile gf);


    void initialize();

    void run();

    /*
    receiver redirecting to pcap
    */

   void receive_message(std::vector<unsigned char> data);

    /*
    receiver redirecting to ethernet
    */
    void receive_message(std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<EthernetFrameInterface> initial_protocol_state, uint32_t time_s, uint32_t time_us);

    /*
    receiver redirecting to ipv4
    */
    void receive_message(std::shared_ptr<Event> calling_event, std::shared_ptr<CommunicationProtocol> payload, std::shared_ptr<IPv4PacketInterface> initial_protocol_state, uint32_t time_s, uint32_t time_us);

    std::shared_ptr<NetworkProperties> get_np() {return np;}
    GFStructs::GeneratorFile get_generatorfile_by_id(uint32_t id);
};
#endif
