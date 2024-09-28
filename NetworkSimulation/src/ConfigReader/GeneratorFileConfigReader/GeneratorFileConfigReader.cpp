#include "GeneratorFileConfigReader.h"
#include "../../UtilityLibraries/StringUtils/StringUtils.h"
#include "../../UtilityLibraries/WayneUtils/wayneFS.hpp"

const std::string GeneratorFileConfigReader::PROTOCOL_STACK_KEY = "PROTOCOL_STACK";
const std::string GeneratorFileConfigReader::CONNECTION_OFFSET_SEC_KEY = "CONNECTION_OFFSET_SEC";
const std::string GeneratorFileConfigReader::CONNECTION_OFFSET_USEC_KEY = "CONNECTION_OFFSET_USEC";
const std::string GeneratorFileConfigReader::REPEATS_AFTER_KEY = "REPEATS_AFTER";
const std::string GeneratorFileConfigReader::CLIENT_KEY = "CLIENT";
const std::string GeneratorFileConfigReader::SERVER_KEY = "SERVER";
const std::string GeneratorFileConfigReader::INIT_CONNECTION_KEY = "INIT_CONNECTION";
const std::string GeneratorFileConfigReader::END_CONNECTION_KEY = "END_CONNECTION";
const std::string GeneratorFileConfigReader::IP_INFO_KEY = "IP_INFO";
const std::string GeneratorFileConfigReader::IP_ADDRESS_KEY = "IP_ADDRESS";
const std::string GeneratorFileConfigReader::TTL_KEY = "TTL";
const std::string GeneratorFileConfigReader::TCP_INFO_KEY = "TCP_INFO";
const std::string GeneratorFileConfigReader::SOURCE_PORT_KEY = "SOURCE_PORT";
const std::string GeneratorFileConfigReader::MSS_KEY = "MSS";
const std::string GeneratorFileConfigReader::PACKETS_SENT_KEY = "PACKETS_SENT";
const std::string GeneratorFileConfigReader::WINDOW_SIZES_KEY = "WINDOW_SIZES";
const std::string GeneratorFileConfigReader::PACKETS_KEY = "PACKETS";
const std::string GeneratorFileConfigReader::INTERPACKET_DELAYS_KEY = "INTERPACKET_DELAYS";
const std::string GeneratorFileConfigReader::SEND_ORDER_KEY = "SEND_ORDER";
const std::string GeneratorFileConfigReader::APPLICATION_DATA_KEY = "APPLICATION_DATA";
const std::string GeneratorFileConfigReader::CONNECTION_END_KEY = "CONNECTION_END";


GeneratorFileConfigReader::GeneratorFileConfigReader(std::vector<std::string> folders)
{
    for (std::string s : folders) {
        read_generator_files(s);
    }
}

GFStructs::Transmitter GeneratorFileConfigReader::read_transmitter_from_generator_file(std::string transmitter_key, boost::property_tree::ptree json) {
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
    t.ip_info.ttl_values = json.get<unsigned char>(jsonpath({transmitter_key, IP_INFO_KEY, TTL_KEY}));

    /*TCP INFO*/

    std::string source_port = json.get<std::string>(jsonpath({transmitter_key, TCP_INFO_KEY, SOURCE_PORT_KEY}));
    if (source_port.compare("application set")) {
        t.tcp_info.source_port = json.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, SOURCE_PORT_KEY}));
    } else {
        t.tcp_info.source_port = 0;
    }

    t.tcp_info.mss = json.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, MSS_KEY}));
    t.tcp_info.packets_sent = json.get<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, PACKETS_SENT_KEY}));
    t.tcp_info.window_sizes = read_json_list<uint16_t>(jsonpath({transmitter_key, TCP_INFO_KEY, WINDOW_SIZES_KEY}), json);

    return t;
}

GFStructs::ApplicationInfo GeneratorFileConfigReader::read_application_data_config(std::string filename) {
    GFStructs::ApplicationInfo ai;

    boost::property_tree::ptree rtree;
    boost::property_tree::read_json(filename, rtree);

    ai.client.packets = read_json_list_of_lists<unsigned char>(jsonpath({CLIENT_KEY, PACKETS_KEY}), rtree);
    ai.client.interpacket_delay = read_json_list<uint32_t>(jsonpath({CLIENT_KEY, INTERPACKET_DELAYS_KEY}), rtree);
    ai.server.packets = read_json_list_of_lists<unsigned char>(jsonpath({SERVER_KEY, PACKETS_KEY}), rtree);
    ai.server.interpacket_delay = read_json_list<uint32_t>(jsonpath({SERVER_KEY, INTERPACKET_DELAYS_KEY}), rtree);
    ai.send_order = {};

    std::vector<std::string> send_order = read_json_list(SEND_ORDER_KEY, rtree);

    for (std::string s : send_order) {
        auto key = GFStructs::s_to_tn.find(s);
        if (key != GFStructs::s_to_tn.end()) {
            ai.send_order.push_back(key->second);
        } else {
            throw std::invalid_argument("SEND_ORDER not CLIENT or SERVER in applicationdata");
        }
    }
    return ai;
}


void GeneratorFileConfigReader::read_generator_file(std::string filename) {

    boost::property_tree::ptree rtree;
    boost::property_tree::read_json(filename, rtree);

    GFStructs::GeneratorFile gen;

    std::vector<std::string> protocol_stack_string = read_json_list(PROTOCOL_STACK_KEY, rtree);
    for (std::string p : protocol_stack_string) {
        auto x = GFStructs::pm_map[p];
        gen.protocol_stack[std::get<GFStructs::LayerModel>(x)] = std::get<GFStructs::ProtocolModel>(x);
    }
    gen.client = read_transmitter_from_generator_file(CLIENT_KEY, rtree);
    gen.server = read_transmitter_from_generator_file(SERVER_KEY, rtree);

    gen.connection_offset_sec = rtree.get<uint32_t>(CONNECTION_OFFSET_SEC_KEY);
    gen.connection_offset_us = rtree.get<uint32_t>(CONNECTION_OFFSET_USEC_KEY);
    gen.connection_close = rtree.get<uint32_t>(CONNECTION_END_KEY);

    gen.repeats_after = rtree.get<uint32_t>(REPEATS_AFTER_KEY);

    gen.application_info = read_application_data_config(rtree.get<std::string>(APPLICATION_DATA_KEY));

    generatorfiles.push_back(gen);
}


void GeneratorFileConfigReader::read_generator_files(std::string folder) {
    std::vector<std::string> generatorfiles = wayne::FS::getStringListDir(folder);

    for (std::string filename : generatorfiles) {
        read_generator_file(filename);
    }
}

