#include "../../../../NetworkSimulation/src/HeaderGenerators/TCPSegment/TCPSegment.h"
#include "../../../../NetworkSimulation/src/HeaderGenerators/Data/Data.h"
#include <memory>


#ifndef TCPSEGMENTHELPER_H
#define TCPSEGMENTHELPER_H
namespace TCPSegmentHelperNS {
    struct defaultPacketArgs{
        uint16_t source_port = 1234;
        uint16_t destination_port = 4321;
        uint32_t sequence_nr = 12;
        uint32_t acknowledgement_nr = 2;
        bool cwr_flag = false;
        bool ece_flag = false;
        bool urg_flag = false;
        bool ack_flag = true;
        bool psh_flag = false;
        bool rst_flag = false;
        bool syn_flag = false;
        bool fin_flag = false;
        uint16_t window_size = 2143;
        uint16_t urgent_pointer = 0;
        uint16_t mss_option = 2122;
        std::shared_ptr<CommunicationProtocol> payload = std::shared_ptr<CommunicationProtocol>(new Data({0x11, 0x12, 0x13}));
    };
    class TCPSegmentHelper {
    public:
        std::shared_ptr<TCPSegmentInterface> get_stdpacket(defaultPacketArgs args
        ) {

            std::shared_ptr<TCPSegmentInterface> p = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());
            p->set_source_port(args.source_port);
            p->set_destination_port(args.destination_port);
            p->set_sequence_nr(args.sequence_nr);
            p->set_acknowledgement_nr(args.acknowledgement_nr);
            p->set_cwr_flag(args.cwr_flag);
            p->set_ece_flag(args.ece_flag);
            p->set_urg_flag(args.urg_flag);
            p->set_ack_flag(args.ack_flag);
            p->set_psh_flag(args.psh_flag);
            p->set_rst_flag(args.rst_flag);
            p->set_syn_flag(args.syn_flag);
            p->set_fin_flag(args.fin_flag);
            p->set_payload(args.payload);
            return p;
        }
    };
}


#endif // TCPSEGMENTHELPER_H
