#ifndef SIMULATORAPPCONFIGREADER_H
#define SIMULATORAPPCONFIGREADER_H

#include "../BaseConfigReader/BaseConfigReader.h"
#include "AppConfigFileStruct.h"

class SimulatorAppConfigReader : BaseConfigReader
{
private:
    ConfigFileStructs::AppConfigFileStruct file;

    static const std::string STREAM_CONFIG_PATH_KEY;

    void readAppConfig(std::string path);
public:
    SimulatorAppConfigReader(std::string filename);
    ConfigFileStructs::AppConfigFileStruct getFile() {return file;}
};

#endif // SIMULATORAPPCONFIGREADER_H
