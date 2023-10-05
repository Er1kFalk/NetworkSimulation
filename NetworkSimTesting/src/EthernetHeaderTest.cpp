/*
 * UnitTest.cpp
 *
 *  Created on: 24 Sept 2023
 *      Author: erik
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "EthernetHeader.h"
#include <string>
#include <array>

EthernetFrame h;

TEST(EthernetFrame, set_destination_address) {
	std::vector<unsigned char> dest = {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x23};
//	std::array<unsigned char, 6> src = {0x12, 0xAB, 0x12, 0x45, 0xBB, 0x24};
//	std::array<unsigned char, 2> ether = {0x01, 0x00};

	h.set_destination_address(dest);
//	EXPECT_TRUE(h.get_destination_address() != dest);
	EXPECT_THAT(h.get_destination_address(), testing::ElementsAreArray(dest));


//	h.set_source_address(src);
//	EXPECT_TRUE(h.getSourceAddress() == src);
//
//	h.set_ethertype(ether);
//	EXPECT_TRUE(h.getEthertype() == ether);
}

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

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
