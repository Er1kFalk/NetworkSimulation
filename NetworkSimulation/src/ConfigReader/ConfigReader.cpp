#include "ConfigReader.h"
#include "../StringUtils/StringUtils.h"
#include "../WayneUtils/wayneFS.hpp"

const std::string ConfigReader::NEST_OPERATOR = ".";

const std::string ConfigReader::CONNECTION_OFFSET_SEC_KEY = "CONNECTION_OFFSET_SEC"; 
const std::string ConfigReader::CONNECTION_OFFSET_USEC_KEY = "CONNECTION_OFFSET_USEC";
const std::string ConfigReader::REPEATS_AFTER_KEY = "REPEATS_AFTER";
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

ConfigReader::ConfigReader(std::vector<std::string> folders) {
    for (std::string s : folders) {
        read_generator_files(s);
    }
}

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


GFStructs::Transmitter ConfigReader::read_transmitter_from_generator_file(std::string transmitter_key, boost::property_tree::ptree json) {
    GFStructs::Transmitter t;

    t.init_connection = json.get<bool>(jsonpath({transmitter_key, INIT_CONNECTION_KEY}));
    t.end_connection = json.get<bool>(jsonpath({transmitter_key, END_CONNECTION_KEY}));

    /*IP INFO*/
    std::string ip_address = json.get<std::string>(jsonpath({transmitter_key, IP_INFO_KEY, IP_ADDRESS_KEY}));
    if (ip_address.compare("application set")) {
        t.ip_info.ip_address = StringUtils::string_to_ipv4_address(ip_address);
    } else {
        t.ip_info.ip_address = {0, 0, 0, 0};
    }
    t.ip_info.ttl_values = read_json_list<unsigned char>(jsonpath({transmitter_key, IP_INFO_KEY, TTL_KEY}), json);

    /*TCP INFO*/
    
    std::string source_port = json.get<std::string>(jsonpath({transmitter_key, TCP_INFO_KEY, SOURCE_PORT_KEY}));
    if (source_port.compare("application set")) {
        t.tcp_info.source_port = json.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, SOURCE_PORT_KEY}));
    } else {
        t.tcp_info.source_port = 0;
    }
    
    t.tcp_info.mss = json.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, MSS_KEY}));
    t.tcp_info.packets_sent = json.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, PACKETS_SENT_KEY}));

    return t;
}


void ConfigReader::read_generator_file(std::string filename) {

    boost::property_tree::ptree rtree;
    boost::property_tree::read_json(filename, rtree);

    GFStructs::GeneratorFile gen;

    gen.client = read_transmitter_from_generator_file(CLIENT_KEY, rtree);
    gen.server = read_transmitter_from_generator_file(SERVER_KEY, rtree);

    gen.connection_offset_sec = rtree.get<uint32_t>(CONNECTION_OFFSET_SEC_KEY);
    gen.connection_offset_us = rtree.get<uint32_t>(CONNECTION_OFFSET_USEC_KEY);
    gen.repeats_after = rtree.get<uint32_t>(REPEATS_AFTER_KEY);

    generatorfiles.push_back(gen);
}


void ConfigReader::read_generator_files(std::string folder) {
    std::vector<std::string> generatorfiles = wayne::FS::getStringListDir(folder);

    for (std::string filename : generatorfiles) {
        read_generator_file(filename);
    }
}
