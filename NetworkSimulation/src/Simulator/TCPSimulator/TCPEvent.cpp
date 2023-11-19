#include "TCPEvent.h"
#include "TCPEventRules.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../MainSimulator/MainSimulator.h"
#include <iostream>

std::map<std::tuple<NetworkLayer, Transmitter>, TCPEventRulePtr> TCPEvent::pass_to_layer = {
    {{NetworkLayer::IPv4, Transmitter::Client}, TCPEventRulePtr(new PassClientStateToIPv4)},
    {{NetworkLayer::IPv4, Transmitter::Server}, TCPEventRulePtr(new PassServerStateToIPv4)}
};

void TCPEvent::apply_rules(std::shared_ptr<BaseScheduler> scheduler) {
    for (auto rule : event_rules) {
        rule->handle(shared_from_this(), scheduler);
    }
    pass_to_layer[{nlayer, tx}]->handle(shared_from_this(), scheduler);
}