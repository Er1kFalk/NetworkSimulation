///*
// * UnitTest.cpp
// *
// *  Created on: 24 Sept 2023
// *      Author: erik
// */
//
#include <gtest/gtest.h>
//#include <gmock/gmock.h>
////#include "EthernetHeader.h"
//#include <string>
//#include <array>
//#include <assert.h>

//EthernetFrame h;

//// testing setter for destination address, when destination addres is of length 6
//TEST(EthernetFrame, set_destination_address) {
//	std::vector<unsigned char> dest = {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x23};
//
//	ASSERT_EQ(dest.size(), 6);
//	ASSERT_NE(h.get_destination_address(), dest);
//
//	h.set_destination_address(dest);
//	EXPECT_THAT(h.get_destination_address(), testing::ElementsAreArray(dest));
//}
//
//// testing setter for destination address, when destination addres is of length < 6
//TEST(EthernetFrame, set_too_short_destination_address) {
//	std::vector<unsigned char> dest = {0x12, 0xAB, 0x12, 0x45, 0xBB};
//	ASSERT_LT(dest.size(), 6);
//	ASSERT_NE(h.get_destination_address(), dest);
//
//	try {
//		h.set_destination_address(dest);
//		FAIL();
//	} catch (std::invalid_argument &e) {
//		EXPECT_STREQ("Destination address must be 6 octets.", e.what());
//		EXPECT_THAT(h.get_destination_address(), testing::Not(testing::ElementsAreArray(dest)));
//	}
//}
//
//// testing setter for destination address, when destination addres is of length > 6
//TEST(EthernetFrame, set_too_long_destination_address) {
//	std::vector<unsigned char> dest = {0x12, 0xAB, 0x12, 0x45, 0xBB, 0xB1, 0xB2};
//	ASSERT_GT(dest.size(), 6);
//	ASSERT_NE(h.get_destination_address(), dest);
//
//	try {
//		h.set_destination_address(dest);
//		FAIL();
//	} catch (std::invalid_argument &e) {
//		EXPECT_STREQ("Destination address must be 6 octets.", e.what());
//		EXPECT_THAT(h.get_destination_address(), testing::Not(testing::ElementsAreArray(dest)));
//	}
//}
//
//TEST(EthernetFrame, set_source_address) {
//	std::vector<unsigned char> src = {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x23};
//}

//TEST(EthernetHeader, TestStringSetters) {
//	h.setEthertype("IPv4");
//	std::array<unsigned char, 2> ipv4 = {0x08, 0x00};
//	EXPECT_TRUE(h.getEthertype() == ipv4);
//
//	h.setEthertype("ARP");
//	std::array<unsigned char, 2> arp = {0x08, 0x06};
//	EXPECT_TRUE(h.getEthertype() == arp);
//
//	h.setEthertype("IPv6");
//	std::array<unsigned char, 2> ipv6 = {0x86, 0xDD};
//	EXPECT_TRUE(h.getEthertype() == ipv6);
//
//	// test exception
//}
