#include "TCPSegmentTests.h"
#include "../../../NetworkSimulation/src/HeaderGenerators/TCPSegment/TCPSegment.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*
set_source_port
*/
TEST(TCPSegment, settingDestinationPort) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    int test_arg = 8192;

    ASSERT_NE(t->get_source_port(), test_arg);
    t->set_source_port(test_arg);
    EXPECT_EQ(t->get_source_port(), test_arg);
}


/*
set_destination_port
*/
TEST(TCPSegment, settingSourcePort) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    int test_arg = 8192;

    ASSERT_NE(t->get_destination_port(), test_arg);
    t->set_destination_port(test_arg);
    EXPECT_EQ(t->get_destination_port(), test_arg);
}



/*
set_sequence_nr
*/

TEST(TCPSegment, settingSequenceNumber) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    int test_arg = 33554432;

    ASSERT_NE(t->get_sequence_nr(), test_arg);
    t->set_sequence_nr(test_arg);
    EXPECT_EQ(t->get_sequence_nr(), test_arg);
}

/*
set_acknowledgement_nr
*/

TEST(TCPSegment, settingAcknowledgementNumber) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    int test_arg = 33554432;

    ASSERT_NE(t->get_acknowledgement_nr(), test_arg);
    t->set_acknowledgement_nr(test_arg);
    EXPECT_EQ(t->get_acknowledgement_nr(), test_arg);
}

/*
set_data_offset
*/

TEST(TCPSegment, settingDataOffsetOnStandardHeader) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_data_offset();
    EXPECT_EQ(t->get_data_offset(), 5);
}

// need test for when adding options

/*
set_cwr_flag
*/

TEST(TCPSegment, settingCWRFlag) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_cwr_flag(true);
    EXPECT_TRUE(t->get_cwr_flag());

    t->set_cwr_flag(false);
    EXPECT_FALSE(t->get_cwr_flag());
}

/*
set_ece_flag
*/

TEST(TCPSegment, settingECEFlag) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_ece_flag(true);
    EXPECT_TRUE(t->get_ece_flag());

    t->set_ece_flag(false);
    EXPECT_FALSE(t->get_ece_flag());
}

/*
set_urg_flag
*/

TEST(TCPSegment, settingURGFlag) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_urg_flag(true);
    EXPECT_TRUE(t->get_urg_flag());

    t->set_urg_flag(false);
    EXPECT_FALSE(t->get_urg_flag());
}

/*
set_ack_flag
*/

TEST(TCPSegment, settingACKFlag) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_ack_flag(true);
    EXPECT_TRUE(t->get_ack_flag());

    t->set_ack_flag(false);
    EXPECT_FALSE(t->get_ack_flag());
}

/*
set_psh_flag
*/

TEST(TCPSegment, settingPSHFlag) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_psh_flag(true);
    EXPECT_TRUE(t->get_psh_flag());

    t->set_psh_flag(false);
    EXPECT_FALSE(t->get_psh_flag());
}

/*
set_psh_flag
*/

TEST(TCPSegment, settingRSTFlag) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_rst_flag(true);
    EXPECT_TRUE(t->get_rst_flag());

    t->set_rst_flag(false);
    EXPECT_FALSE(t->get_rst_flag());
}

/*
set_syn_flag
*/

TEST(TCPSegment, settingSYNFlag) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_syn_flag(true);
    EXPECT_TRUE(t->get_syn_flag());

    t->set_syn_flag(false);
    EXPECT_FALSE(t->get_syn_flag());
}

/*
set_fin_flag
*/

TEST(TCPSegment, settingFINFlag) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    t->set_fin_flag(true);
    EXPECT_TRUE(t->get_fin_flag());

    t->set_fin_flag(false);
    EXPECT_FALSE(t->get_fin_flag());
}

/*
set_window_size
*/

TEST(TCPSegment, settingWindowSize) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    uint16_t test = 0x2DCA;

    ASSERT_NE(t->get_window_size(), test);
    t->set_window_size(test);

    EXPECT_EQ(t->get_window_size(), test);
}

/*
set_urgent_pointer
*/

TEST(TCPSegment, settingUrgentPointer) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    uint16_t test = 0x2DCA;

    ASSERT_NE(t->get_urgent_pointer(), test);
    t->set_urgent_pointer(test);

    EXPECT_EQ(t->get_urgent_pointer(), test);
}
