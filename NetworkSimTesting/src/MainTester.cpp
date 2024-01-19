/*
 * MainTester.cpp
 *
 *  Created on: 10 Oct 2023
 *      Author: erik
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tests/StringUtilsTests.h"
#include "tests/BitOperationsTests.h"
#include "tests/EthernetHeaderTests.h"
#include "tests/IPv4PacketTests.h"
#include "tests/ProtocolUtilsTests.h"
#include "tests/TCPSegmentTests.h"
#include "../../NetworkSimulation/src/UtilityLibraries/BitOperations/BitOperations.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
