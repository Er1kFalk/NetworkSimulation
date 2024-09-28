#include "BaseConfigReader.h"
#include "../../UtilityLibraries/StringUtils/StringUtils.h"
#include "../../UtilityLibraries/WayneUtils/wayneFS.hpp"

const std::string BaseConfigReader::NEST_OPERATOR = ".";

BaseConfigReader::BaseConfigReader() {

}

std::string BaseConfigReader::jsonpath(std::vector<std::string> v) {
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
