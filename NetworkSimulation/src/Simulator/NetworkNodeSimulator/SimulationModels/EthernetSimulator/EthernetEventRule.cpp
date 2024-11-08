#include "EthernetEventRule.h"
#include "../BaseScheduler/BaseScheduler.h"
#include "../../NetworkNodeSimulator.h"

void SendEthernetData::handle(EthernetEventPtr e) {
    e->get_parent()->receive_message(e->get_ethernet_frame()->header_payload_to_array());
}
