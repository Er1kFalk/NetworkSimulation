#ifndef GENERATORFILESTRUCT_H_
#define GENERATORFILESTRUCT_H_

#include <vector>
#include <array>
#include <stdint.h>
#include <map>
#include <string>
#include <tuple>


namespace GFStructs {
    enum class ProtocolModel {TCP, IPv4, Ethernet};
    enum LayerModel {Application, Transport, Network, Link};
    enum class TransmittingNow {Client, Server};
    extern std::map<std::string, std::tuple<LayerModel, ProtocolModel>> pm_map;
    extern std::map<std::string, TransmittingNow> s_to_tn;

    struct IPInfo {
        std::vector<unsigned char> ip_address;
        unsigned char ttl_values;
    };

    struct TCPInfo {
        uint16_t source_port;
        uint16_t destination_port;
        uint16_t mss;
        uint16_t packets_sent;
        std::vector<uint16_t> window_sizes;
    };

    struct Transmitter {
        bool init_connection;
        bool end_connection;
        std::array<unsigned char, 6> mac_address;
        IPInfo ip_info;
        TCPInfo tcp_info;
    };

    struct ApplicationTransmitter {
        std::vector<std::vector<unsigned char>> packets;
        std::vector<uint32_t> interpacket_delay;
    };

    struct ApplicationInfo {
        ApplicationTransmitter client;
        ApplicationTransmitter server;
        std::vector<TransmittingNow> send_order;
    };

    struct GeneratorFile {
        std::map<LayerModel, ProtocolModel> protocol_stack;
        uint32_t connection_offset_sec;
        uint32_t connection_offset_us;
        uint32_t repeats_after;
        ApplicationInfo application_info;
        Transmitter client;
        Transmitter server;
    };
}



#endif