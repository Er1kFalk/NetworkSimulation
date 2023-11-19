#include "TCPSegmentTests.h"
#include "../../../NetworkSimulation/src/TCPSegment/TCPSegment.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*
USER STORIES FOR SETTING DESTINATION PORT
*/
TEST(TCPSegment, settingDestinationPort) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    int test_arg = 8192;

    ASSERT_NE(t->get_source_port(), test_arg);
    t->set_source_port(test_arg);
    EXPECT_EQ(t->get_source_port(), test_arg);
}


/*
USER STORIES FOR SETTING SOURCE PORT
*/
TEST(TCPSegment, settingSourcePort) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    int test_arg = 8192;

    ASSERT_NE(t->get_destination_port(), test_arg);
    t->set_destination_port(test_arg);
    EXPECT_EQ(t->get_destination_port(), test_arg);
}



/*
USER STORIES FOR SETTING SEQUENCE NUMBER
*/

TEST(TCPSegment, settingSequenceNumber) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    int test_arg = 33554432;

    ASSERT_NE(t->get_sequence_nr(), test_arg);
    t->set_sequence_nr(test_arg);
    EXPECT_EQ(t->get_sequence_nr(), test_arg);
}

