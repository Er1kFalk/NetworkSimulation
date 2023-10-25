#include "IPv4PacketTests.h"
#include "IPv4Packet/IPv4Packet.h"
#include "Helpers/IPv4PacketHelper.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

IPv4PacketHelper packet_helper;

/* DSCP USE CASES*/

TEST(IPv4Packet, userSetsDscp) {
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket();
    ASSERT_EQ(stdpacket->get_dscp(), 2);

    stdpacket->set_dscp(4);
    EXPECT_EQ(stdpacket->get_dscp(), 4);
}

TEST(IPv4Packet, userSetsDscpToMaxValue) {
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket();
    ASSERT_EQ(stdpacket->get_dscp(), 2);

    stdpacket->set_dscp(63);
    EXPECT_EQ(stdpacket->get_dscp(), 63);
}

TEST(IPv4Packet, userSetsDscpToMoreThanMaxValue) {
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket();
    ASSERT_EQ(stdpacket->get_dscp(), 2);

    try {
        stdpacket->set_dscp(64);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "DSCP values must be between 0-63");
        EXPECT_EQ(stdpacket->get_dscp(), 2);
    }
}