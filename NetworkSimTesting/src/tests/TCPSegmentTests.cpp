#include "TCPSegmentTests.h"
#include "../../../NetworkSimulation/src/HeaderGenerators/TCPSegment/TCPSegment.h"
#include "../../../NetworkSimulation/src/UtilityLibraries/ProtocolUtils/ProtocolUtils.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Helpers/TCPSegmentHelper.h"

namespace TCPSegmentTestsVars {
    TCPSegmentHelperNS::TCPSegmentHelper packet_helper;
}

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

/*
set_ipv4_pseudo_header
*/

TEST(TCPSegment, settingIpv4PseudoHeader) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    std::vector<unsigned char> test_src = {0, 1, 2, 3};
    std::vector<unsigned char> test_dest = {4, 5, 6, 7};

    std::vector<unsigned char> test = {0, 1, 2, 3, 4, 5, 6, 7, 0, 0x06, 0, 20};

    ASSERT_THAT(t->get_ipv4_pseudo_header(), testing::Not(testing::ElementsAreArray(test)));
    t->set_ipv4_pseudo_header(test_src, test_dest);

    EXPECT_THAT(t->get_ipv4_pseudo_header(), testing::ElementsAreArray(test));
}

TEST(TCPSegment, settingIpv4PseudoHeaderWithTooLongIPv4DestinationAddress) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    std::vector<unsigned char> test_src = {0, 1, 2, 3, 5};
    std::vector<unsigned char> test_dest = {4, 5, 6, 7};

    try {
        t->set_ipv4_pseudo_header(test_src, test_dest);
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "source_ip_address must be of size 4");
    }
}

TEST(TCPSegment, settingIpv4PseudoHeaderWithTooShortIPv4DestinationAddress) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    std::vector<unsigned char> test_src = {0, 1, 2};
    std::vector<unsigned char> test_dest = {4, 5, 6, 7};

    try {
        t->set_ipv4_pseudo_header(test_src, test_dest);
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "source_ip_address must be of size 4");
    }
}

TEST(TCPSegment, settingIpv4PseudoHeaderWithTooLongIPv4SourceAddress) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    std::vector<unsigned char> test_src = {0, 1, 2, 3};
    std::vector<unsigned char> test_dest = {4, 5, 6, 7, 5};

    try {
        t->set_ipv4_pseudo_header(test_src, test_dest);
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "destination_ip_address must be of size 4");
    }
}

TEST(TCPSegment, settingIpv4PseudoHeaderWithTooShortIPv4SourceAddress) {
    std::shared_ptr<TCPSegmentInterface> t = std::shared_ptr<TCPSegmentInterface>(new TCPSegment());

    std::vector<unsigned char> test_src = {0, 1, 2, 3};
    std::vector<unsigned char> test_dest = {4, 5, 6};

    try {
        t->set_ipv4_pseudo_header(test_src, test_dest);
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "destination_ip_address must be of size 4");
    }
}

/*
set_checksum()
*/

TEST(TCPSegment, settingTCPChecksum) {
    TCPSegmentHelperNS::defaultPacketArgs args;
    std::shared_ptr<TCPSegmentInterface> t = TCPSegmentTestsVars::packet_helper.get_stdpacket(args);
    t->set_ipv4_pseudo_header({0,1,2,3}, {4,5,6,7});

    // Check that checksum is wrong when it hasn't been set
    std::vector<unsigned char> test_no_checksum = t->get_ipv4_pseudo_header();
    for (unsigned char c : t->header_payload_to_array()) {test_no_checksum.push_back(c);}
    if (test_no_checksum.size() % 2 != 0) test_no_checksum.push_back(0); // checksum is calculated over padded array
    EXPECT_FALSE(ProtocolUtils::verify_internet_checksum(test_no_checksum, 0)); // 0 since checksum is included in the array

    t->set_checksum();

    // it should now be the case that the tcp pseudo header + tcp header w. data has a verified checksum
    std::vector<unsigned char> test_with_checksum = t->get_ipv4_pseudo_header();
    for (unsigned char c : t->header_payload_to_array()) {test_with_checksum.push_back(c);}
    if (test_with_checksum.size() % 2 != 0) test_with_checksum.push_back(0);

    EXPECT_TRUE(ProtocolUtils::verify_internet_checksum(test_with_checksum, 0));
}

TEST(TCPSegment, settingTCPChecksumWithoutPseuodHeader) {
    TCPSegmentHelperNS::defaultPacketArgs args;
    std::shared_ptr<TCPSegmentInterface> t = TCPSegmentTestsVars::packet_helper.get_stdpacket(args);
    ASSERT_NE(t->get_ipv4_pseudo_header().size(), 12); // pseudo header is not set

    try {
        t->set_checksum();
        FAIL();
    } catch (std::invalid_argument e){
        EXPECT_STREQ(e.what(), "cannot calculate checksum when ipv4 pseudo header not set");
    }
}

