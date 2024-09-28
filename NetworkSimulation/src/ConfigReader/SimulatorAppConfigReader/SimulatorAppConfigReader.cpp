#include "SimulatorAppConfigReader.h"

const std::string SimulatorAppConfigReader::STREAM_CONFIG_PATH_KEY = "StreamConfigPath";


SimulatorAppConfigReader::SimulatorAppConfigReader(std::string filename)
{
    this->readAppConfig(filename);
}

void SimulatorAppConfigReader::readAppConfig(std::string filename) {
    boost::property_tree::ptree rtree;
    boost::property_tree::read_json(filename, rtree);

    ConfigFileStructs::AppConfigFileStruct f;

    f.streamConfigPath = read_json_list(STREAM_CONFIG_PATH_KEY, rtree);
    this->file = f;
}

