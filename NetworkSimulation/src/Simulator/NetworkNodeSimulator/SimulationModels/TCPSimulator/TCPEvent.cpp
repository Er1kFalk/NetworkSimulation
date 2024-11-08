#include "TCPEvent.h"
#include "TCPEventRules.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../../NetworkNodeSimulator.h"

std::map<std::tuple<GFStructs::ProtocolModel, GFStructs::TransmittingNow>, TCPEventRulePtr> TCPEvent::pass_to_layer = {
    {{GFStructs::ProtocolModel::IPv4, GFStructs::TransmittingNow::Client}, TCPEventRulePtr(new PassClientStateToIPv4)},
    {{GFStructs::ProtocolModel::IPv4, GFStructs::TransmittingNow::Server}, TCPEventRulePtr(new PassServerStateToIPv4)}
};

void TCPEvent::apply_rules(std::shared_ptr<BaseScheduler> scheduler) {
    for (auto rule : event_rules) {
        rule->handle(shared_from_this(), scheduler);
    }
    auto genfile = this->get_parent()->get_generatorfile_by_id(this->get_id());
    auto nwlayer = genfile.protocol_stack.find(GFStructs::LayerModel::Network)->second;
    pass_to_layer[{nwlayer, get_transmitter()}]->handle(shared_from_this(), scheduler);
}
