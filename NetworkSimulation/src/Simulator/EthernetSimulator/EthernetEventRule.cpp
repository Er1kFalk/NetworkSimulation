#include "EthernetEventRule.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../MainSimulator/MainSimulator.h"

void SendEthernetData::handle(EthernetEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    scheduler->get_parent()->receive_message(e->get_ethernet_frame()->header_payload_to_array(), 0);
}