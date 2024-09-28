#ifndef APPCONFIGFILESTRUCT_H
#define APPCONFIGFILESTRUCT_H

#include <string>
#include <vector>

namespace ConfigFileStructs {
    struct AppConfigFileStruct {
        std::vector<std::string> streamConfigPath;
    };
}

#endif // APPCONFIGFILESTRUCT_H
