#ifndef GENERATORFILECONFIGREADER_H
#define GENERATORFILECONFIGREADER_H

#include "../BaseConfigReader/BaseConfigReader.h"
#include "GeneratorFileStruct.h"

class GeneratorFileConfigReader : BaseConfigReader
{
private:
    std::vector<GFStructs::GeneratorFile> generatorfiles; // vector of loaded generator files
    std::vector<std::string> folders; // folder locationS of generator files

    /* JSON KEYS*/
    static const std::string PROTOCOL_STACK_KEY;
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
    static const std::string WINDOW_SIZES_KEY;
    static const std::string PACKETS_KEY;
    static const std::string INTERPACKET_DELAYS_KEY;
    static const std::string SEND_ORDER_KEY;
    static const std::string APPLICATION_DATA_KEY;
    static const std::string CONNECTION_END_KEY;

    GFStructs::Transmitter read_transmitter_from_generator_file(std::string transmitter_key, boost::property_tree::ptree json);
    void read_generator_file(std::string filename);
    void read_generator_files(std::string folder);
    GFStructs::ApplicationInfo read_application_data_config(std::string filename);
public:
    GeneratorFileConfigReader(std::vector<std::string> folders);
    std::vector<GFStructs::GeneratorFile> get_generatorfiles() {return generatorfiles;}
};

#endif // GENERATORFILECONFIGREADER_H
