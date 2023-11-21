#include "ConfigReader.h"
#include "../StringUtils/StringUtils.h"

const std::string ConfigReader::NEST_OPERATOR = ".";
const std::string ConfigReader::CLIENT_KEY = "CLIENT";
const std::string ConfigReader::SERVER_KEY = "SERVER";
const std::string ConfigReader::INIT_CONNECTION_KEY = "INIT_CONNECTION";
const std::string ConfigReader::END_CONNECTION_KEY = "END_CONNECTION";
const std::string ConfigReader::IP_INFO_KEY = "IP_INFO";
const std::string ConfigReader::IP_ADDRESS_KEY = "IP_ADDRESS";
const std::string ConfigReader::TTL_KEY = "TTL";
const std::string ConfigReader::TCP_INFO_KEY = "TCP_INFO";
const std::string ConfigReader::SOURCE_PORT_KEY = "SOURCE_PORT";
const std::string ConfigReader::MSS_KEY = "MSS";
const std::string ConfigReader::PACKETS_SENT_KEY = "PACKETS_SENT";

std::string ConfigReader::jsonpath(std::vector<std::string> v) {
    if (v.size() == 0) {
        throw std::invalid_argument("vector must not be of length 0");
    }
    if (v.size() == 1) {
        return v[0];
    }
    assert(v.size() >= 2);

    std::string jsonpath = v[0];
    for (int i = 1; i < v.size(); i++) {
        jsonpath += NEST_OPERATOR + v[i];
    }

    return jsonpath;
}


Transmitter ConfigReader::read_transmitter_from_generator_file(std::string filename, std::string transmitter_key) {
    boost::property_tree::ptree root_tree;
    boost::property_tree::read_json(filename, root_tree);

    Transmitter t;

    t.init_connection = root_tree.get<bool>(jsonpath({transmitter_key, INIT_CONNECTION_KEY}));
    t.end_connection = root_tree.get<bool>(jsonpath({transmitter_key, END_CONNECTION_KEY}));

    /*IP INFO*/
    std::string ip_address = root_tree.get<std::string>(transmitter_key + NEST_OPERATOR + IP_INFO_KEY + NEST_OPERATOR + IP_ADDRESS_KEY);
    if (ip_address.compare("application set")) {
        t.ip_info.ip_address = StringUtils::string_to_ipv4_address(ip_address);
    } else {
        t.ip_info.ip_address = {0, 0, 0, 0};
    }
    t.ip_info.ttl_values = read_json_list<unsigned char>(jsonpath({transmitter_key, IP_INFO_KEY, TTL_KEY}), root_tree);

    /*TCP INFO*/
    
    std::string source_port = root_tree.get<std::string>(jsonpath({transmitter_key, TCP_INFO_KEY, SOURCE_PORT_KEY}));
    if (source_port.compare("application set")) {
        t.tcp_info.source_port = root_tree.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, SOURCE_PORT_KEY}));
    } else {
        t.tcp_info.source_port = 0;
    }
    
    t.tcp_info.mss = root_tree.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, MSS_KEY}));
    t.tcp_info.packets_sent = root_tree.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, PACKETS_SENT_KEY}));

    return t;
}


void ConfigReader::read_generator_file(std::string filename) {

    Transmitter client;
    Transmitter server;

    client = read_transmitter_from_generator_file(filename, CLIENT_KEY);
    server = read_transmitter_from_generator_file(filename, SERVER_KEY);
}
