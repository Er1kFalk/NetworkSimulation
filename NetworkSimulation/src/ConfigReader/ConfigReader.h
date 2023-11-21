#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

#include <tuple>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "GeneratorFileStruct.h"


class ConfigReader {
private:
    static uint32_t id; // MAYBE not needed
    std::vector<GFStructs::GeneratorFile> generatorfiles;
    std::vector<std::string> folders;

    /*The operator BOOST use to go into (nested) json objects*/
    static const std::string NEST_OPERATOR;

    /* JSON KEYS*/
    static const std::string CONNECTION_OFFSET_SEC_KEY; /*seconds*/
    static const std::string CONNECTION_OFFSET_USEC_KEY; /*microseconds*/
    static const std::string REPEATS_AFTER_KEY; /*in sec_KEYonds*/
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

    /*Given a list of json keys, it makes a path that can be used 
    to read the corresponding value in a nested json structure*/
    std::string jsonpath(std::vector<std::string> v);

    /*function to convert json list to a c++ vector*/
    template<typename T>
    std::vector<T> read_json_list(std::string key, boost::property_tree::ptree json) {
        std::vector<T> v;
        
        for (boost::property_tree::ptree::value_type &val : json.get_child(key)) {
            v.push_back(std::stoi(val.second.data()));
        }

        return v;
    }

    GFStructs::Transmitter read_transmitter_from_generator_file(std::string transmitter_key, boost::property_tree::ptree json);
    void read_generator_file(std::string filename);
    void read_generator_files(std::string folder);
public:
    ConfigReader(std::vector<std::string> folders);
    std::vector<GFStructs::GeneratorFile> get_generatorfiles() {return generatorfiles;}
};

#endif