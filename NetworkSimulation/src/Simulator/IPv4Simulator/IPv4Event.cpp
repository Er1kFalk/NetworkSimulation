#include "IPv4Event.h"
#include "IPv4EventRule.h"

std::map<LinkLayer, IPv4EventRulePtr> IPv4Event::pass_to_layer = {
    {LinkLayer::Ethernet, IPv4EventRulePtr(new PassIPv4DataToEthernet)}
};

void IPv4Event::apply_rules(std::shared_ptr<BaseScheduler> scheduler) {
    for (auto rule : event_rules) {
        rule->handle(shared_from_this(), scheduler);
    }
    pass_to_layer[llayer]->handle(shared_from_this(), scheduler);
}