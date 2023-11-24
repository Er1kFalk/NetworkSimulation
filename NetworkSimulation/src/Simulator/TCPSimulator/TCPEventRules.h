#ifndef EVENTRULES_H_
#define EVENTRULES_H_

#include <tuple>
#include <memory>
#include "../../TCPSegment/TCPSegmentInterface.h"
#include "../NetworkProperties.h"
#include "TCPSimulatorTypeDefs.h"

class BaseScheduler;

class TCPEventRule {
protected:
    static std::shared_ptr<RandomUtils> generator;
public:
    virtual void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) = 0;
    // static void init_connection(TCPEventPtr e);
    // static void send_syn(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler);

    static void send_data(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler);
};

class SendSyn : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class ReceiveSynAck : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class SendInitialAck : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class SendData : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class ServerSendData : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class ClientSendData : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class ServerSendAck : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class ClientSendAck : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class PassServerStateToIPv4 : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

class PassClientStateToIPv4 : public TCPEventRule {
    void handle(TCPEventPtr e, std::shared_ptr<BaseScheduler> scheduler) override;
};

#endif