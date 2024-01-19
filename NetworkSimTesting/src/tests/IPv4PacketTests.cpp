#include "IPv4PacketTests.h"
#include "../../NetworkSimulation/src/HeaderGenerators/IPv4Packet/IPv4Packet.h"


#include "Helpers/IPv4PacketHelper.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../NetworkSimulation/src/HeaderGenerators/ProtocolConstants/ProtocolConstants.h"
#include "../../../NetworkSimulation/src/UtilityLibraries/BitOperations/BitOperations.h"
#include "../../../NetworkSimulation/src/UtilityLibraries/ProtocolUtils/ProtocolUtils.h"

IPv4PacketHelper packet_helper;

/*VERSION USE CASES*/
TEST(IPv4PacketInterface, UserInitializesInitializesIPv4PacketInterfaceAndVersionIs4) {
    defaultPacketArgs args;
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);

    EXPECT_EQ(stdpacket->get_version(), 4);
}


/* DSCP USE CASES*/

TEST(IPv4PacketInterface, userSetsDscp) {
    defaultPacketArgs args;
    args.dscp = 0;
    ASSERT_EQ(args.dscp, IPv4Constants::BoundaryConstants::DSCP_MIN);
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);

    EXPECT_EQ(stdpacket->get_dscp(), 0);
}

TEST(IPv4PacketInterface, userSetsDscpToMaxValue) {
    defaultPacketArgs args;
    args.dscp = 63;
    ASSERT_EQ(args.dscp, IPv4Constants::BoundaryConstants::DSCP_MAX);
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);

    EXPECT_EQ(stdpacket->get_dscp(), 63);
}

TEST(IPv4PacketInterface, userSetsDscpToMoreThanMaxValue) {
    defaultPacketArgs args;
    args.dscp = 64;
    ASSERT_GT(args.dscp, IPv4Constants::BoundaryConstants::DSCP_MAX);
    std::unique_ptr<IPv4PacketInterface> stdpacket;

    try {
        stdpacket = packet_helper.get_stdpacket(args);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "DSCP values must be between 0-63");
    }
}

/*ECN USE CASES*/
TEST(IPv4PacketInterface, userSetsEcnToMinValue) {
    defaultPacketArgs args;
    args.ecn = 0;
    ASSERT_EQ(args.ecn, IPv4Constants::BoundaryConstants::ECN_MIN);
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
    
    EXPECT_EQ(stdpacket->get_ecn(), 0);
}

TEST(IPv4PacketInterface, userSetsEcnToMaxValue) {
    defaultPacketArgs args;
    args.ecn = 3;
    ASSERT_EQ(args.ecn, IPv4Constants::BoundaryConstants::ECN_MAX);
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
    
    EXPECT_EQ(stdpacket->get_ecn(), 3);
}

TEST(IPv4PacketInterface, userSetsEcnToMoreThanMaxValue) {
    defaultPacketArgs args;
    args.ecn = 4;
    ASSERT_GT(args.ecn, IPv4Constants::BoundaryConstants::ECN_MAX);
    std::unique_ptr<IPv4PacketInterface> stdpacket;
    

    try{
        stdpacket = packet_helper.get_stdpacket(args);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "ECN values must be between 0-3");
    }
}

/*OPTIONS USE CASES*/

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithoutOptions) {
    defaultPacketArgs args;
    args.options = {};
    args.payload = std::shared_ptr<CommunicationProtocol>(new Data(std::vector<unsigned char>(625, 1)));
    ASSERT_EQ(args.options.size(), 0);
    ASSERT_EQ(args.payload->header_to_array().size(), 625);
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
    
    stdpacket->recalculate_fields();

    // std header without options => no padding, ihl is always 5
    EXPECT_EQ(stdpacket->get_options().size(), 0); 
    EXPECT_EQ(stdpacket->get_ihl(), 5);
    EXPECT_THAT(stdpacket->get_total_length(), 0x0285);
}

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithOptionThatIsAMultipleOfFourOctets) {
    defaultPacketArgs args;
    args.options = {0x01, 0x02, 0x03, 0x04};
    args.payload = std::shared_ptr<CommunicationProtocol>(new Data(std::vector<unsigned char>(625, 1)));
    ASSERT_EQ(args.payload->header_to_array().size(), 625);
    ASSERT_EQ(args.options.size(), 4);

    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
    
    stdpacket->recalculate_fields();

    // std header without options => no padding, ihl is always 5
    EXPECT_THAT(stdpacket->get_options(), testing::ElementsAreArray({0x01, 0x02, 0x03, 0x04}));
    EXPECT_EQ(stdpacket->get_ihl(), 6);
    EXPECT_THAT(stdpacket->get_total_length(), 0x0289);
}

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithOptionThatIsNotAMultipleOfFourOctets) {
    defaultPacketArgs args;
    args.options = {0x01, 0x02, 0x03, 0x04, 0x05};
    args.payload = std::shared_ptr<CommunicationProtocol>(new Data(std::vector<unsigned char>(625, 1)));
    ASSERT_EQ(args.payload->header_to_array().size(), 625);
    ASSERT_EQ(args.options.size(), 5); 
    
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
    stdpacket->recalculate_fields();

    // std header without options => no padding, ihl is always 5
    EXPECT_THAT(stdpacket->get_options(), testing::ElementsAreArray({0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00}));
    EXPECT_EQ(stdpacket->get_ihl(), 7);
    EXPECT_THAT(stdpacket->get_total_length(), 0x028D);
}

/*IDENTIFICATION USE CASES */

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithIdentification625) {
    defaultPacketArgs args;
    args.identfication_id = 625;
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
    
    EXPECT_THAT(stdpacket->get_identification(), 0x0271);
}


/*MF AND DF FLAG USE CASES*/
TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithDFTrueAndMFFalse) {
    defaultPacketArgs args;
    args.df = true;
    args.mf = false;
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);

    unsigned char flags = stdpacket->header_to_array()[6];
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 7), 0); // reserved
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 6), 1); // df
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 5), 0); // mf
}

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithDFFalseAndMFTrue) {
    defaultPacketArgs args;
    args.df = false;
    args.mf = true;
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
        
    unsigned char flags = stdpacket->header_to_array()[6];
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 7), 0); // reserved
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 6), 0); // df
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 5), 1); // mf
}

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithDFFalseAndMFFalse) {
    defaultPacketArgs args;
    args.df = false;
    args.mf = false;
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
        
    unsigned char flags = stdpacket->header_to_array()[6];
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 7), 0); // reserved
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 6), 0); // df
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 5), 0); // mf
}

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithDFTrueAndMFTrue) {
    defaultPacketArgs args;
    args.df = true;
    args.mf = true;
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
        
    unsigned char flags = stdpacket->header_to_array()[6];
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 7), 0); // reserved
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 6), 1); // df
    EXPECT_EQ(BitOperations::read_nth_lsb(flags, 5), 1); // mf
}

/*FRAGMENT OFFSET USE CASES*/
TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithMinFragmentOffsetAndNoSetFlags) {
    defaultPacketArgs args;
    args.df = false;
    args.mf = false;
    args.offset = IPv4Constants::BoundaryConstants::FRAGMENT_OFFSET_MIN;
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
        
    EXPECT_EQ(stdpacket->get_fragment_offset(), 0);
}

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithMaxFragmentOffsetAndNoSetFlags) {
    defaultPacketArgs args;
    args.df = false;
    args.mf = false;
    args.offset = IPv4Constants::BoundaryConstants::FRAGMENT_OFFSET_MAX;
    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);
        
    EXPECT_EQ(stdpacket->get_fragment_offset(), 0x1FFF);
}

TEST(IPv4PacketInterface, userInitializesIPv4PacketInterfaceWithGreaterThanMaxFragmentOffsetAndNoSetFlags) {
    defaultPacketArgs args;
    args.df = false;
    args.mf = false;
    args.offset = 8192;
    ASSERT_GT(args.offset, IPv4Constants::BoundaryConstants::FRAGMENT_OFFSET_MAX);
    std::unique_ptr<IPv4PacketInterface> stdpacket;

    try {
        stdpacket = packet_helper.get_stdpacket(args);
        FAIL();
    } catch (std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "Offset must be between 0 and 8191");
    }
        
}

TEST(IPv4PacketInterface, userInitializesIPv4PacketAndChecksumIsCorrect) {
    defaultPacketArgs args;

    std::unique_ptr<IPv4PacketInterface> stdpacket = packet_helper.get_stdpacket(args);

    stdpacket->recalculate_fields();

    EXPECT_TRUE(ProtocolUtils::verify_internet_checksum(stdpacket->header_to_array(), 0)); // putting 0 here, since the checksum is included in header_to_array
}