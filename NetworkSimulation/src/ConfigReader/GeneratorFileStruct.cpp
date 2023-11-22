#include "GeneratorFileStruct.h"

std::map<std::string, std::tuple<GFStructs::LayerModel, GFStructs::ProtocolModel>> GFStructs::pm_map = {
    {"TCP", {GFStructs::LayerModel::Transport, GFStructs::ProtocolModel::TCP}},
    {"IPv4", {GFStructs::LayerModel::Network, GFStructs::ProtocolModel::IPv4}},
    {"Ethernet", {GFStructs::LayerModel::Link, GFStructs::ProtocolModel::Ethernet}}
};
