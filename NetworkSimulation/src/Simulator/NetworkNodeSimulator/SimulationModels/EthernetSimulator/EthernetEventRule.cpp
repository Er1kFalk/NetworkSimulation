#include "EthernetEventRule.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../../NetworkNodeSimulator.h"

void SendEthernetData::handle(EthernetEventPtr e, std::shared_ptr<BaseScheduler> scheduler) {
    e->get_parent()->receive_message(e->get_ethernet_frame()->header_payload_to_array(), scheduler->get_scheduler_time_sec(), scheduler->get_scheduler_time_us());
}
