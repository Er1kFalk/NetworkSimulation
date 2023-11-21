#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

#include <tuple>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

struct IPInfo {
    std::vector<unsigned char> ip_address;
    std::vector<unsigned char> ttl_values;
};

struct TCPInfo {
    uint16_t source_port;
    uint16_t destination_port;
    uint16_t mss;
    uint16_t packets_sent;
};

struct Transmitter {
    bool init_connection;
    bool end_connection;
    std::array<unsigned char, 6> mac_address;
    IPInfo ip_info;
	TCPInfo tcp_info;
};

struct GeneratorFileStruct {
    Transmitter client;
    Transmitter server;
};

class ConfigReader {
private:
    static uint32_t id;
    GeneratorFileStruct generatorfile;

    static const std::string NEST_OPERATOR;
    static const std::string CLIENT_KEY;
    static const std::string SERVER_KEY;
    static const std::string INIT_CONNECTION_KEY;
    static const std::string END_CONNECTION_KEY;
    static const std::string IP_INFO_KEY;
    static const std::string IP_ADDRESS_KEY;
    static const std::string TTL_KEY;
    static const std::string TCP_INFO_KEY;
    static const std::string SOURCE_PORT_KEY;
    static const std::string MSS_KEY;
    static const std::string PACKETS_SENT_KEY;

    std::string jsonpath(std::vector<std::string> v);

    template<typename T>
    std::vector<T> read_json_list(std::string key, boost::property_tree::ptree json) {
        std::vector<T> v;
        
        for (boost::property_tree::ptree::value_type &val : json.get_child(key)) {
            v.push_back(std::stoi(val.second.data()));
        }

        return v;
    }

    Transmitter read_transmitter_from_generator_file(std::string filename, std::string transmitter_key);
    void read_generator_file(std::string filename);
public:
    void read_generator_files(std::string folder);

};

#endif