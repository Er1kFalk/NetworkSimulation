#include "TCPEvent.h"
#include "TCPEventRules.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../NetworkNodeSimulator/NetworkNodeSimulator.h"
#include <iostream>

std::map<std::tuple<GFStructs::ProtocolModel, Transmitter>, TCPEventRulePtr> TCPEvent::pass_to_layer = {
    {{GFStructs::ProtocolModel::IPv4, Transmitter::Client}, TCPEventRulePtr(new PassClientStateToIPv4)},
    {{GFStructs::ProtocolModel::IPv4, Transmitter::Server}, TCPEventRulePtr(new PassServerStateToIPv4)}
};

void TCPEvent::apply_rules(std::shared_ptr<BaseScheduler> scheduler) {
    for (auto rule : event_rules) {
        rule->handle(shared_from_this(), scheduler);
    }
    auto genfile = scheduler->get_parent()->get_generatorfile_by_id(this->get_id());
    auto nwlayer = genfile.protocol_stack.find(GFStructs::LayerModel::Network)->second;
    pass_to_layer[{nwlayer, get_transmitter()}]->handle(shared_from_this(), scheduler);
}